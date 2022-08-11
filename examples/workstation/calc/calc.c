/*$file${.::calc.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: calc.qm
* File:  ${.::calc.c}
*
* This code has been generated by QM 5.2.1 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This generated code is open source software: you can redistribute it under
* the terms of the GNU General Public License as published by the Free
* Software Foundation.
*
* This code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* NOTE:
* Alternatively, this generated code may be distributed under the terms
* of Quantum Leaps commercial licenses, which expressly supersede the GNU
* General Public License and are specifically designed for licensees
* interested in retaining the proprietary status of their code.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${.::calc.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"   /* QP/C */
#include "bsp.h"   /* board support package */
#include "calc.h"  /* application */

/*$declare${SMs::Calc} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::Calc} .............................................................*/
typedef struct {
/* protected: */
    QHsm super;

/* private: */
    double operand1;
    uint8_t operator;
} Calc;

/* protected: */
static QState Calc_initial(Calc * const me, void const * const par);
static QState Calc_on(Calc * const me, QEvt const * const e);
static QState Calc_error(Calc * const me, QEvt const * const e);
static QState Calc_negated1(Calc * const me, QEvt const * const e);
static QState Calc_ready(Calc * const me, QEvt const * const e);
static QState Calc_result(Calc * const me, QEvt const * const e);
static QState Calc_begin(Calc * const me, QEvt const * const e);
static QState Calc_operand1(Calc * const me, QEvt const * const e);
static QState Calc_zero1(Calc * const me, QEvt const * const e);
static QState Calc_int1(Calc * const me, QEvt const * const e);
static QState Calc_frac1(Calc * const me, QEvt const * const e);
static QState Calc_opEntered(Calc * const me, QEvt const * const e);
static QState Calc_negated2(Calc * const me, QEvt const * const e);
static QState Calc_operand2(Calc * const me, QEvt const * const e);
static QState Calc_zero2(Calc * const me, QEvt const * const e);
static QState Calc_int2(Calc * const me, QEvt const * const e);
static QState Calc_frac2(Calc * const me, QEvt const * const e);
static QState Calc_final(Calc * const me, QEvt const * const e);
/*$enddecl${SMs::Calc} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static Calc l_calc;    /* the only instance of the Calc class */

/* global-scope definitions ---------------------------------------*/
QHsm * const the_calc = &l_calc.super;  /* "opaque" pointer to MSM */

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.9.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${SMs::Calc_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::Calc_ctor} ........................................................*/
void Calc_ctor(void) {
    Calc *me = &l_calc;
    QHsm_ctor(&me->super, Q_STATE_CAST(&Calc_initial));
}
/*$enddef${SMs::Calc_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${SMs::Calc} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::Calc} .............................................................*/

/*${SMs::Calc::SM} .........................................................*/
static QState Calc_initial(Calc * const me, void const * const par) {
    /*${SMs::Calc::SM::initial} */
    BSP_clear();
    (void)par; /* unused parameter */

    QS_FUN_DICTIONARY(&Calc_on);
    QS_FUN_DICTIONARY(&Calc_error);
    QS_FUN_DICTIONARY(&Calc_negated1);
    QS_FUN_DICTIONARY(&Calc_ready);
    QS_FUN_DICTIONARY(&Calc_result);
    QS_FUN_DICTIONARY(&Calc_begin);
    QS_FUN_DICTIONARY(&Calc_operand1);
    QS_FUN_DICTIONARY(&Calc_zero1);
    QS_FUN_DICTIONARY(&Calc_int1);
    QS_FUN_DICTIONARY(&Calc_frac1);
    QS_FUN_DICTIONARY(&Calc_opEntered);
    QS_FUN_DICTIONARY(&Calc_negated2);
    QS_FUN_DICTIONARY(&Calc_operand2);
    QS_FUN_DICTIONARY(&Calc_zero2);
    QS_FUN_DICTIONARY(&Calc_int2);
    QS_FUN_DICTIONARY(&Calc_frac2);
    QS_FUN_DICTIONARY(&Calc_final);

    return Q_TRAN(&Calc_on);
}

/*${SMs::Calc::SM::on} .....................................................*/
static QState Calc_on(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on} */
        case Q_ENTRY_SIG: {
            BSP_message("on-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on} */
        case Q_EXIT_SIG: {
            BSP_message("on-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::initial} */
        case Q_INIT_SIG: {
            BSP_message("on-INIT;");
            status_ = Q_TRAN(&Calc_ready);
            break;
        }
        /*${SMs::Calc::SM::on::C} */
        case C_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_on);
            break;
        }
        /*${SMs::Calc::SM::on::OFF} */
        case OFF_SIG: {
            status_ = Q_TRAN(&Calc_final);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::error} ..............................................*/
static QState Calc_error(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::error} */
        case Q_ENTRY_SIG: {
            BSP_message("error-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::error} */
        case Q_EXIT_SIG: {
            BSP_message("error-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::negated1} ...........................................*/
static QState Calc_negated1(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::negated1} */
        case Q_ENTRY_SIG: {
            BSP_message("negated1-ENTRY;");
            BSP_negate();
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::negated1} */
        case Q_EXIT_SIG: {
            BSP_message("negated1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::negated1::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_zero1);
            break;
        }
        /*${SMs::Calc::SM::on::negated1::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /*${SMs::Calc::SM::on::negated1::POINT} */
        case POINT_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /*${SMs::Calc::SM::on::negated1::OPER} */
        case OPER_SIG: {
            /*${SMs::Calc::SM::on::negated1::OPER::[e->key=='-']} */
            if (Q_EVT_CAST(CalcEvt)->key_code == KEY_MINUS) {
                ;
                status_ = Q_HANDLED();
            }
            /*${SMs::Calc::SM::on::negated1::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        /*${SMs::Calc::SM::on::negated1::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::ready} ..............................................*/
static QState Calc_ready(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::ready} */
        case Q_ENTRY_SIG: {
            BSP_message("ready-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::ready} */
        case Q_EXIT_SIG: {
            BSP_message("ready-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::ready::initial} */
        case Q_INIT_SIG: {
            BSP_message("ready-INIT;");
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        /*${SMs::Calc::SM::on::ready::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_zero1);
            break;
        }
        /*${SMs::Calc::SM::on::ready::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_clear();
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /*${SMs::Calc::SM::on::ready::POINT} */
        case POINT_SIG: {
            BSP_clear();
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /*${SMs::Calc::SM::on::ready::OPER} */
        case OPER_SIG: {
            me->operand1 = BSP_get_value();
            me->operator = Q_EVT_CAST(CalcEvt)->key_code;
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::ready::result} ......................................*/
static QState Calc_result(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::ready::result} */
        case Q_ENTRY_SIG: {
            BSP_message("result-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::ready::result} */
        case Q_EXIT_SIG: {
            BSP_message("result-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_ready);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::ready::begin} .......................................*/
static QState Calc_begin(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::ready::begin} */
        case Q_ENTRY_SIG: {
            BSP_message("begin-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::ready::begin} */
        case Q_EXIT_SIG: {
            BSP_message("begin-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::ready::begin::OPER} */
        case OPER_SIG: {
            /*${SMs::Calc::SM::on::ready::begin::OPER::[e->key=='-']} */
            if (Q_EVT_CAST(CalcEvt)->key_code == KEY_MINUS) {
                status_ = Q_TRAN(&Calc_negated1);
            }
            /*${SMs::Calc::SM::on::ready::begin::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_ready);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand1} ...........................................*/
static QState Calc_operand1(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand1} */
        case Q_ENTRY_SIG: {
            BSP_message("operand1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1} */
        case Q_EXIT_SIG: {
            BSP_message("operand1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        /*${SMs::Calc::SM::on::operand1::OPER} */
        case OPER_SIG: {
            me->operand1 = BSP_get_value();
            me->operator = Q_EVT_CAST(CalcEvt)->key_code;
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        /*${SMs::Calc::SM::on::operand1::EQUALS} */
        case EQUALS_SIG: {
            status_ = Q_TRAN(&Calc_result);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand1::zero1} ....................................*/
static QState Calc_zero1(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand1::zero1} */
        case Q_ENTRY_SIG: {
            BSP_message("zero1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::zero1} */
        case Q_EXIT_SIG: {
            BSP_message("zero1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::zero1::DIGIT_0} */
        case DIGIT_0_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::zero1::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /*${SMs::Calc::SM::on::operand1::zero1::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand1::int1} .....................................*/
static QState Calc_int1(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand1::int1} */
        case Q_ENTRY_SIG: {
            BSP_message("int1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::int1} */
        case Q_EXIT_SIG: {
            BSP_message("int1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::int1::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /*${SMs::Calc::SM::on::operand1::int1::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand1::frac1} ....................................*/
static QState Calc_frac1(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand1::frac1} */
        case Q_ENTRY_SIG: {
            BSP_message("frac1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::frac1} */
        case Q_EXIT_SIG: {
            BSP_message("frac1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::frac1::POINT} */
        case POINT_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand1::frac1::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::opEntered} ..........................................*/
static QState Calc_opEntered(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::opEntered} */
        case Q_ENTRY_SIG: {
            BSP_message("opEntered-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::opEntered} */
        case Q_EXIT_SIG: {
            BSP_message("opEntered-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::opEntered::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_zero2);
            break;
        }
        /*${SMs::Calc::SM::on::opEntered::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_clear();
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /*${SMs::Calc::SM::on::opEntered::POINT} */
        case POINT_SIG: {
            BSP_clear();
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /*${SMs::Calc::SM::on::opEntered::OPER} */
        case OPER_SIG: {
            /*${SMs::Calc::SM::on::opEntered::OPER::[e->key=='-']} */
            if (Q_EVT_CAST(CalcEvt)->key_code == KEY_MINUS) {
                status_ = Q_TRAN(&Calc_negated2);
            }
            /*${SMs::Calc::SM::on::opEntered::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::negated2} ...........................................*/
static QState Calc_negated2(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::negated2} */
        case Q_ENTRY_SIG: {
            BSP_message("negated2-ENTRY;");
            BSP_negate();
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::negated2} */
        case Q_EXIT_SIG: {
            BSP_message("negated2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::negated2::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_zero2);
            break;
        }
        /*${SMs::Calc::SM::on::negated2::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /*${SMs::Calc::SM::on::negated2::POINT} */
        case POINT_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /*${SMs::Calc::SM::on::negated2::OPER} */
        case OPER_SIG: {
            /*${SMs::Calc::SM::on::negated2::OPER::[e->key=='-']} */
            if (Q_EVT_CAST(CalcEvt)->key_code == KEY_MINUS) {
                ;
                status_ = Q_HANDLED();
            }
            /*${SMs::Calc::SM::on::negated2::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        /*${SMs::Calc::SM::on::negated2::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand2} ...........................................*/
static QState Calc_operand2(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand2} */
        case Q_ENTRY_SIG: {
            BSP_message("operand2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2} */
        case Q_EXIT_SIG: {
            BSP_message("operand2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        /*${SMs::Calc::SM::on::operand2::EQUALS} */
        case EQUALS_SIG: {
            /*${SMs::Calc::SM::on::operand2::EQUALS::[BSP_eval()]} */
            if (BSP_eval(me->operand1, me->operator, BSP_get_value())) {
                status_ = Q_TRAN(&Calc_result);
            }
            /*${SMs::Calc::SM::on::operand2::EQUALS::[else]} */
            else {
                status_ = Q_TRAN(&Calc_error);
            }
            break;
        }
        /*${SMs::Calc::SM::on::operand2::OPER} */
        case OPER_SIG: {
            /*${SMs::Calc::SM::on::operand2::OPER::[BSP_eval()]} */
            if (BSP_eval(me->operand1, me->operator, BSP_get_value())) {
                me->operand1 = BSP_get_value();
                me->operator = Q_EVT_CAST(CalcEvt)->key_code;
                status_ = Q_TRAN(&Calc_opEntered);
            }
            /*${SMs::Calc::SM::on::operand2::OPER::[else]} */
            else {
                status_ = Q_TRAN(&Calc_error);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand2::zero2} ....................................*/
static QState Calc_zero2(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand2::zero2} */
        case Q_ENTRY_SIG: {
            BSP_message("zero2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::zero2} */
        case Q_EXIT_SIG: {
            BSP_message("zero2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::zero2::DIGIT_0} */
        case DIGIT_0_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::zero2::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /*${SMs::Calc::SM::on::operand2::zero2::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand2::int2} .....................................*/
static QState Calc_int2(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand2::int2} */
        case Q_ENTRY_SIG: {
            BSP_message("int2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::int2} */
        case Q_EXIT_SIG: {
            BSP_message("int2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::int2::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /*${SMs::Calc::SM::on::operand2::int2::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::on::operand2::frac2} ....................................*/
static QState Calc_frac2(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::on::operand2::frac2} */
        case Q_ENTRY_SIG: {
            BSP_message("frac2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::frac2} */
        case Q_EXIT_SIG: {
            BSP_message("frac2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::frac2::POINT} */
        case POINT_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /*${SMs::Calc::SM::on::operand2::frac2::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_EVT_CAST(CalcEvt)->key_code);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}

/*${SMs::Calc::SM::final} ..................................................*/
static QState Calc_final(Calc * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::Calc::SM::final} */
        case Q_ENTRY_SIG: {
            BSP_message("final-ENTRY;");
            BSP_exit();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*$enddef${SMs::Calc} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
