// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2020-2021 The PCTM developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PCTM_CORE_NEW_GUI_PRUNNABLE_H
#define PCTM_CORE_NEW_GUI_PRUNNABLE_H

class Runnable {
public:
    virtual void run(int type) = 0;
    virtual void onError(QString error, int type) = 0;
};

#endif //PCTM_CORE_NEW_GUI_PRUNNABLE_H
