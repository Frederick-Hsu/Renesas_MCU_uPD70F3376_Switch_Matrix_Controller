/**************************************************************************************************
 * File name    : general.h
 * Description  : Define some general types applied in all projects.
 * Creator      : Frederick Hsu
 * Creation date: Sat.  21 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#ifndef GENERAL_H
#define GENERAL_H

    typedef enum Status
    {
        TRUE = 1,
        FALSE = 0,

        INFEASIBLE = -2,
        ERROR = -1,
        OK = 0,
        OVERFLOW = 3,

        PASS = 0,
        FAIL = 1
    }
    Status, Status_t;

    typedef int Boolean;

#endif  /* GENERAL_H */
