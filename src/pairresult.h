// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2020-2021 The PCTM developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PCTM_PAIRRESULT_H
#define PCTM_PAIRRESULT_H


class PairResult {

public:
    PairResult(bool res):result(res){}
    PairResult(bool res, std::string* statusStr):result(res), status(statusStr){}

    bool result;
    std::string* status = nullptr;
};


#endif //PCTM_PAIRRESULT_H
