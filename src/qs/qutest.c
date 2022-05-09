/*============================================================================
* QP/C Real-Time Embedded Framework (RTEF)
* Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
*
* SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
*
* This software is dual-licensed under the terms of the open source GNU
* General Public License version 3 (or any later version), or alternatively,
* under the terms of one of the closed source Quantum Leaps commercial
* licenses.
*
* The terms of the open source GNU General Public License version 3
* can be found at: <www.gnu.org/licenses/gpl-3.0>
*
* The terms of the closed source Quantum Leaps commercial licenses
* can be found at: <www.state-machine.com/licensing>
*
* Redistributions in source code must retain this top-level comment block.
* Plagiarizing this software to sidestep the license obligations is illegal.
*
* Contact information:
* <www.state-machine.com>
* <info@state-machine.com>
============================================================================*/
/*!
* @date Last updated on: 2021-12-23
* @version Last updated for: @ref qpc_7_0_0
*
* @file
* @brief QF/C stub for QUTEST unit testing
*/
/* only build when Q_UTEST is defined */
#ifdef Q_UTEST

#define QP_IMPL       /* this is QP implementation */
#include "qf_port.h"  /* QF port */
#include "qf_pkg.h"   /* QF package-scope interface */
#include "qassert.h"  /* QP embedded systems-friendly assertions */
#include "qs_port.h"  /* include QS port */
#include "qs_pkg.h"   /* QS facilities for pre-defined trace records */

Q_DEFINE_THIS_MODULE("qutest")

/* Global objects ==========================================================*/
uint8_t volatile QF_intNest;

/* QF functions ============================================================*/
/*! @static @public @memberof QF */
void QF_init(void) {
    /* Clear the internal QF variables, so that the framework can start
    * correctly even if the startup code fails to clear the uninitialized
    * data (as is required by the C Standard).
    */
    QF_maxPool_      = 0U;
    QF_subscrList_   = (QSubscrList *)0;
    QF_maxPubSignal_ = 0;
    QF_intNest       = 0U;

    QF_bzero(&QF_active_[0],       sizeof(QF_active_));
    QF_bzero(&QS_rxPriv_.readySet, sizeof(QS_rxPriv_.readySet));
}
/*..........................................................................*/
/*! @static @public @memberof QF */
void QF_stop(void) {
    QS_onReset();
}
/*..........................................................................*/
/*! @static @public @memberof QF */
int_t QF_run(void) {
    /* function dictionaries for the standard API */
    QS_FUN_DICTIONARY(&QActive_post_);
    QS_FUN_DICTIONARY(&QActive_postLIFO_);
    QS_FUN_DICTIONARY(&QS_processTestEvts_);

    /* produce the QS_QF_RUN trace record */
    QS_CRIT_STAT_
    QS_BEGIN_PRE_(QS_QF_RUN, 0U)
    QS_END_PRE_()

    QS_onTestLoop(); /* run the test loop */
    QS_onCleanup();  /* application cleanup */
    return 0; /* return no error */
}

/*..........................................................................*/
/*! @private @memberof QActive */
void QActive_start_(QActive * const me, uint_fast8_t prio,
                    QEvt const * * const qSto, uint_fast16_t const qLen,
                    void * const stkSto, uint_fast16_t const stkSize,
                    void const * const par)
{
    (void)stkSto;  /* unused parameter */
    (void)stkSize; /* unused parameter */

    /* priority must be in range */
    Q_REQUIRE_ID(200, (0U < prio) && (prio <= QF_MAX_ACTIVE));

    QEQueue_init(&me->eQueue, qSto, qLen); /* initialize the built-in queue */
    me->prio = (uint8_t)prio; /* set the current priority of the AO */

    QF_add_(me); /* make QF aware of this active object */

    QHSM_INIT(&me->super, par, me->prio); /* the top-most initial tran. */
}

/*==========================================================================*/
static void QHsmDummy_init_(QHsm * const me, void const * const par,
                            uint_fast8_t const qs_id);
static void QHsmDummy_dispatch_(QHsm * const me, QEvt const * const e,
                               uint_fast8_t const qs_id);

/*..........................................................................*/
/*! "constructor" of QHsmDummy
* @public @memberof QHsmDummy
*/
void QHsmDummy_ctor(QHsmDummy * const me) {
    static struct QHsmVtable const vtable = {  /* QHsm virtual table */
        &QHsmDummy_init_,
        &QHsmDummy_dispatch_
#ifdef Q_SPY
        ,&QHsm_getStateHandler_
#endif
    };
    /* superclass' ctor */
    QHsm_ctor(&me->super, Q_STATE_CAST(0));
    me->super.vptr = &vtable;  /* hook the vptr */
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QHsmDummy_init_(QHsm * const me, void const * const par,
                               uint_fast8_t const qs_id)
{
    (void)par;   /* unused parameter */

    QS_CRIT_STAT_
    QS_BEGIN_PRE_(QS_QEP_STATE_INIT, qs_id)
        QS_OBJ_PRE_(me);        /* this state machine object */
        QS_FUN_PRE_(me->state.fun); /* the source state */
        QS_FUN_PRE_(me->temp.fun);  /* the target of the initial transition */
    QS_END_PRE_()
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QHsmDummy_dispatch_(QHsm * const me, QEvt const * const e,
                                uint_fast8_t const qs_id)
{
    QS_CRIT_STAT_
    QS_BEGIN_PRE_(QS_QEP_DISPATCH, qs_id)
        QS_TIME_PRE_();             /* time stamp */
        QS_SIG_PRE_(e->sig);        /* the signal of the event */
        QS_OBJ_PRE_(me);            /* this state machine object */
        QS_FUN_PRE_(me->state.fun); /* the current state */
    QS_END_PRE_()
}

/*==========================================================================*/
static void QActiveDummy_init_(QHsm * const me, void const * const par,
                               uint_fast8_t const qs_id);
static void QActiveDummy_dispatch_(QHsm * const me, QEvt const * const e,
                               uint_fast8_t const qs_id);
static bool QActiveDummy_post_(QActive * const me, QEvt const * const e,
                   uint_fast16_t const margin, void const * const sender);
static void QActiveDummy_postLIFO_(QActive * const me, QEvt const * const e);
static void QActiveDummy_start_(QActive * const me, uint_fast8_t prio,
                                QEvt const * * const qSto, uint_fast16_t qLen,
                                void *stkSto, uint_fast16_t stkSize,
                                void const * const par);

/*..........................................................................*/
/*! "constructor" of QActiveDummy
* @public @memberof QActiveDummy
*/
void QActiveDummy_ctor(QActiveDummy * const me) {
    static QActiveVtable const vtable = {  /* QActive virtual table */
        { &QActiveDummy_init_,
          &QActiveDummy_dispatch_
#ifdef Q_SPY
          ,&QHsm_getStateHandler_
#endif
        },
        &QActiveDummy_start_,
        &QActiveDummy_post_,
        &QActiveDummy_postLIFO_
    };
    /* superclass' ctor */
    QActive_ctor(&me->super, Q_STATE_CAST(0));
    me->super.super.vptr = &vtable.super;  /* hook the vptr */
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QActiveDummy_start_(QActive * const me, uint_fast8_t prio,
                                QEvt const * * const qSto, uint_fast16_t qLen,
                                void *stkSto, uint_fast16_t stkSize,
                                void const * const par)
{
    /* No special preconditions for checking parameters to allow starting
    * dummy AOs the exact same way as the real counterparts.
    */
    (void)qSto;    /* unusuded parameter */
    (void)qLen;    /* unusuded parameter */
    (void)stkSto;  /* unusuded parameter */
    (void)stkSize; /* unusuded parameter */

    me->prio = (uint8_t)prio; /* set the current priority of the AO */

    QF_add_(me); /* make QF aware of this active object */

    /* the top-most initial tran. (virtual) */
    QHSM_INIT(&me->super, par, me->prio);
    //QS_FLUSH();
}
//............................................................................
#ifdef QF_ACTIVE_STOP
/*! @public @memberof QActive */
void QActive_stop(QActive * const me) {
    QActive_unsubscribeAll(me); /* unsubscribe from all events */
    QF_remove_(me); /* remove this object from QF */
}
#endif

/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QActiveDummy_init_(QHsm * const me, void const * const par,
                               uint_fast8_t const qs_id)
{
    (void)qs_id; /* unused parameter */

    QHsmDummy_init_(me, par, ((QActive const *)me)->prio);
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QActiveDummy_dispatch_(QHsm * const me, QEvt const * const e,
                                   uint_fast8_t const qs_id)
{
    (void)qs_id; /* unused parameter */

    QHsmDummy_dispatch_(me, e, ((QActive const *)me)->prio);
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static bool QActiveDummy_post_(QActive * const me, QEvt const * const e,
                               uint_fast16_t const margin,
                               void const * const sender)
{
    QS_TEST_PROBE_DEF(&QActive_post_)

    /* test-probe#1 for faking queue overflow */
    bool status = true;
    QS_TEST_PROBE_ID(1,
        status = false;
        if (margin == QF_NO_MARGIN) {
            /* fake assertion Mod=qf_actq,Loc=110 */
            Q_onAssert("qf_actq", 110);
        }
    )

    QF_CRIT_STAT_
    QF_CRIT_E_();

    /* is it a dynamic event? */
    if (e->poolId_ != 0U) {
        QF_EVT_REF_CTR_INC_(e); /* increment the reference counter */
    }

    uint_fast8_t const rec = (status ? (uint_fast8_t)QS_QF_ACTIVE_POST
                             : (uint_fast8_t)QS_QF_ACTIVE_POST_ATTEMPT);
    QS_BEGIN_NOCRIT_PRE_(rec, me->prio)
        QS_TIME_PRE_();      /* timestamp */
        QS_OBJ_PRE_(sender); /* the sender object */
        QS_SIG_PRE_(e->sig); /* the signal of the event */
        QS_OBJ_PRE_(me);     /* this active object */
        QS_2U8_PRE_(e->poolId_, e->refCtr_); /* pool Id & refCtr of the evt */
        QS_EQC_PRE_(0U);     /* number of free entries */
        QS_EQC_PRE_(margin); /* margin requested */
    QS_END_NOCRIT_PRE_()

    /* callback to examine the posted event under the same conditions
    * as producing the #QS_QF_ACTIVE_POST trace record, which are:
    * the local filter for this AO ('me->prio') is set
    */
    if ((QS_priv_.locFilter[me->prio >> 3U]
         & (1U << (me->prio & 7U))) != 0U)
    {
        QS_onTestPost(sender, me, e, status);
    }
    QF_CRIT_X_();

    /* recycle the event immediately, because it was not really posted */
    QF_gc(e);

    return status; /* the event is "posted" correctly */
}
/*..........................................................................*/
/*! @private @memberof QActiveDummy */
static void QActiveDummy_postLIFO_(QActive * const me, QEvt const * const e) {
    QS_TEST_PROBE_DEF(&QActive_postLIFO_)

    /* test-probe#1 for faking queue overflow */
    QS_TEST_PROBE_ID(1,
        /* fake assertion Mod=qf_actq,Loc=210 */
        Q_onAssert("qf_actq", 210);
    )

    QF_CRIT_STAT_
    QF_CRIT_E_();

    /* is it a dynamic event? */
    if (e->poolId_ != 0U) {
        QF_EVT_REF_CTR_INC_(e); /* increment the reference counter */
    }

    QS_BEGIN_NOCRIT_PRE_(QS_QF_ACTIVE_POST_LIFO, me->prio)
        QS_TIME_PRE_();      /* timestamp */
        QS_SIG_PRE_(e->sig); /* the signal of this event */
        QS_OBJ_PRE_(me);     /* this active object */
        QS_2U8_PRE_(e->poolId_, e->refCtr_); /* pool Id & refCtr of the evt */
        QS_EQC_PRE_(0U);     /* number of free entries */
        QS_EQC_PRE_(0U);     /* min number of free entries */
    QS_END_NOCRIT_PRE_()

    /* callback to examine the posted event under the same conditions
    * as producing the #QS_QF_ACTIVE_POST trace record, which are:
    * the local filter for this AO ('me->prio') is set
    */
    if ((QS_priv_.locFilter[me->prio >> 3U]
         & (1U << (me->prio & 7U))) != 0U)
    {
        QS_onTestPost((QActive *)0, me, e, true);
    }

    QF_CRIT_X_();

    /* recycle the event immediately, because it was not really posted */
    QF_gc(e);
}

/*==========================================================================*/
/*! @static @private @memberof QS */
void QS_processTestEvts_(void) {
    QS_TEST_PROBE_DEF(&QS_processTestEvts_)

    /* return immediately (do nothing) for Test Probe != 0 */
    QS_TEST_PROBE(return;)

    while (QPSet_notEmpty(&QS_rxPriv_.readySet)) {
        uint_fast8_t const p = QPSet_findMax(&QS_rxPriv_.readySet);
        QActive * const a = QF_active_[p];

        /* perform the run-to-completion (RTC) step...
        * 1. retrieve the event from the AO's event queue, which by this
        *    time must be non-empty and The "Vanialla" kernel asserts it.
        * 2. dispatch the event to the AO's state machine.
        * 3. determine if event is garbage and collect it if so
        */
        QEvt const * const e = QActive_get_(a);
        QHSM_DISPATCH(&a->super, e, a->prio);
        QF_gc(e);

        if (a->eQueue.frontEvt == (QEvt *)0) { /* empty queue? */
            QPSet_remove(&QS_rxPriv_.readySet, p);
        }
    }
}
/*..........................................................................*/
/* The testing version of system tick processing performs as follows:
* 1. If the Current Time Event (TE) Object is defined and the TE is armed,
*    the TE is disarmed (if one-shot) and then posted to the recipient AO.
* 2. The linked-list of all armed Time Events is updated.
*/
/*! @static @private @memberof QS */
void QS_tickX_(uint_fast8_t const tickRate, void const * const sender) {
    QF_CRIT_STAT_
    QF_CRIT_E_();

    QTimeEvt *prev = &QF_timeEvtHead_[tickRate];

    QS_BEGIN_NOCRIT_PRE_(QS_QF_TICK, 0U)
        ++prev->ctr;
        QS_TEC_PRE_(prev->ctr); /* tick ctr */
        QS_U8_PRE_(tickRate);   /* tick rate */
    QS_END_NOCRIT_PRE_()

    /* is current Time Event object provided? */
    QTimeEvt *t = (QTimeEvt *)QS_rxPriv_.currObj[TE_OBJ];
    if (t != (QTimeEvt *)0) {

        /* the time event must be armed */
        Q_ASSERT_ID(810, t->ctr != 0U);

        /* temp. for volatile */
        QActive * const act = (QActive * const)(t->act);

        /* the recipient AO must be provided */
        Q_ASSERT_ID(820, act != (QActive *)0);

        /* periodic time evt? */
        if (t->interval != 0U) {
            t->ctr = t->interval; /* rearm the time event */
        }
        else { /* one-shot time event: automatically disarm */
            t->ctr = 0U; /* auto-disarm */
            /* mark time event 't' as NOT linked */
            t->super.refCtr_ &= (uint8_t)(~(uint8_t)QTE_IS_LINKED);

            QS_BEGIN_NOCRIT_PRE_(QS_QF_TIMEEVT_AUTO_DISARM, act->prio)
                QS_OBJ_PRE_(t);        /* this time event object */
                QS_OBJ_PRE_(act);      /* the target AO */
                QS_U8_PRE_(tickRate);  /* tick rate */
            QS_END_NOCRIT_PRE_()
        }

        QS_BEGIN_NOCRIT_PRE_(QS_QF_TIMEEVT_POST, act->prio)
            QS_TIME_PRE_();            /* timestamp */
            QS_OBJ_PRE_(t);            /* the time event object */
            QS_SIG_PRE_(t->super.sig); /* signal of this time event */
            QS_OBJ_PRE_(act);          /* the target AO */
            QS_U8_PRE_(tickRate);      /* tick rate */
        QS_END_NOCRIT_PRE_()

        QF_CRIT_X_(); /* exit critical section before posting */

        QACTIVE_POST(act, &t->super, sender); /* asserts if queue overflows */

        QF_CRIT_E_();
    }

    /* update the linked list of time events */
    for (;;) {
        t = prev->next;  /* advance down the time evt. list */

        /* end of the list? */
        if (t == (QTimeEvt *)0) {

            /* any new time events armed since the last run of QF_tickX_()? */
            if (QF_timeEvtHead_[tickRate].act != (void *)0) {

                /* sanity check */
                Q_ASSERT_CRIT_(830, prev != (QTimeEvt *)0);
                prev->next = (QTimeEvt *)QF_timeEvtHead_[tickRate].act;
                QF_timeEvtHead_[tickRate].act = (void *)0;
                t = prev->next;  /* switch to the new list */
            }
            else {
                break; /* all currently armed time evts. processed */
            }
        }

        /* time event scheduled for removal? */
        if (t->ctr == 0U) {
            prev->next = t->next;
            /* mark time event 't' as NOT linked */
            t->super.refCtr_ &= (uint8_t)(~(uint8_t)QTE_IS_LINKED);
            /* do NOT advance the prev pointer */
            QF_CRIT_X_(); /* exit crit. section to reduce latency */

            /* prevent merging critical sections, see NOTE1 below  */
            QF_CRIT_EXIT_NOP();
        }
        else {
            prev = t; /* advance to this time event */
            QF_CRIT_X_(); /* exit crit. section to reduce latency */

            /* prevent merging critical sections, see NOTE1 below  */
            QF_CRIT_EXIT_NOP();
        }
        QF_CRIT_E_(); /* re-enter crit. section to continue */
    }

    QF_CRIT_X_();
}
/*..........................................................................*/
/*! @static @private @memberof QS */
void QS_test_pause_(void) {
    QS_beginRec_((uint_fast8_t)QS_TEST_PAUSED);
    QS_endRec_();
    QS_onTestLoop();
}

/*==========================================================================*/
Q_NORETURN Q_onAssert(char const * const module, int_t const location) {
    QS_BEGIN_NOCRIT_PRE_(QS_ASSERT_FAIL, 0U)
        QS_TIME_PRE_();
        QS_U16_PRE_(location);
        QS_STR_PRE_((module != (char *)0) ? module : "?");
    QS_END_NOCRIT_PRE_()

    QS_onFlush(); /* flush the assertion record to the host */
    QS_onTestLoop(); /* loop to wait for commands (typically reset) */
    QS_onReset(); /* in case the QUTEST loop ever returns, reset manually */
    for (;;) { /* QS_onReset() should not return, but to ensure no-return */
    }
}

#endif /* Q_UTEST */
