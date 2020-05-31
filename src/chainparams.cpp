// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2020-2021 The PCTM developers


// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "consensus/merkle.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>

#include "chainparamsseeds.h"

std::string CDNSSeedData::getHost(uint64_t requiredServiceBits) const {
    //use default host for non-filter-capable seeds or if we use the default service bits (NODE_NETWORK)
    if (!supportsServiceBitsFiltering || requiredServiceBits == NODE_NETWORK)
        return host;

    return strprintf("x%x.%s", requiredServiceBits, host);
}

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock
CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    const char *pszTimestamp = "CNN May 06 2020 Supreme embarrassment: The flush heard around the country";
    const CScript genesisOutputScript = CScript() << ParseHex("045C39AE04ECDC90D0055C78774D12BC406F5C0521B8B9F4E99201FB576205543D32C66CA5F55E33F1024724873EA04B83524C69D187C7C418ACAE59B8A5F868D6") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
                (0, uint256S("000008d0d565c1bc0fa245fc4d8b31f1de1438979c2b3b73234364f60b2673ef"));

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1588820064, // * UNIX timestamp of last checkpoint block
        0,    // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        100        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
                (0, uint256S("0x000005350f609d8dee013062226f9459d859d95db8023623b8c22b07a322e565"));

static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1589594325,
        11,
        100};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
                (0, uint256S("000005350f609d8dee013062226f9459d859d95db8023623b8c22b07a322e565"));
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1577169143,
        0,
        100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1588820064, 1502666, 0x1e0ffff0, 1, 1 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256("0x000008d0d565c1bc0fa245fc4d8b31f1de1438979c2b3b73234364f60b2673ef"));
        assert(genesis.hashMerkleRoot == uint256("0x3a2353b4f74192b56cc2cfbbfe49796948f47cece1b9ea3278fd11aed287b4d1"));

        consensus.nPremineAmount = 10799888 * COIN;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit = ~UINT256_ZERO >> 20;   // PCTM starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMasternodeCollateral = 100000 * COIN;
        consensus.nMaxMoneyOut = 21000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04a36346b0f188d3c6d4d78ff194698f0f55736364536b5c9752b9b440c135fce6e36cf484a3a7054cad2bfdb114ffb8cd8f1a1631b6689c6cc81404827b157eb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

        // height-based activations
        consensus.height_last_PoW = 259200;
        consensus.height_last_ZC_AccumCheckpoint = 1190;
        consensus.height_last_ZC_WrappedSerials = 1205;
        consensus.height_start_BIP65 = 1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_MessSignaturesV2 = 1;  // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1200;
        consensus.height_start_StakeModifierV2 = 1200;
        consensus.height_start_TimeProtoV2 = 1;
        consensus.height_start_ZC = 1210;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_PublicSpends = 1215;
        consensus.height_start_ZC_SerialRangeCheck = 1220;
        consensus.height_start_ZC_SerialsV2 = 1225;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // validation by-pass
        consensus.nPctmBadBlockTime = 1471401614;    // Skip nBit validation of Block 259201 per PR #915
        consensus.nPctmBadBlockBits = 0x1c056dac;    // Skip nBit validation of Block 259201 per PR #915

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1588820664; // 10 minutes after genesis
        consensus.ZC_WrappedSerialsSupply = 0 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x60;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xa7;
        nDefaultPort = 12122;

        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("pactumcoin.com", "mainnet.seed.pactumcoin.com"));     // Primary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);  //starting with A
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  //starting with 8
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        //Mainnet pubkey starts with 'anpb'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xbe)(0x89)(0xf4).convert_to_container < std::vector < unsigned char > > ();
        //Mainnet privkey start with 'anpv'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xb6)(0xf6)(0x1a).convert_to_container < std::vector < unsigned char > > ();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x0f)(0xc9).convert_to_container < std::vector < unsigned char > > ();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1577169143, 454267, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000005350f609d8dee013062226f9459d859d95db8023623b8c22b07a322e565"));
        assert(genesis.hashMerkleRoot == uint256S("0x3a2353b4f74192b56cc2cfbbfe49796948f47cece1b9ea3278fd11aed287b4d1"));

        consensus.nPremineAmount = 1000000 * COIN;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 20;   // PCTM starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMasternodeCollateral = 100000 * COIN;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04bc6f5acaf8e1fa263264655c6bca1e34bf33f103ced69ddef31df881bf7155db2c226b3358b236a6d5a6a2de42f30e7de46cec9fb26317fec9845eab36b23e6e";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

        // height based activations
        consensus.height_last_PoW = 200;
        consensus.height_last_ZC_AccumCheckpoint = 201;
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_BIP65 = 1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_MessSignaturesV2 = 201;      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 201;
        consensus.height_start_StakeModifierV2 = 201;
        consensus.height_start_TimeProtoV2 = 201;
        consensus.height_start_ZC = 201;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_PublicSpends = 201;
        consensus.height_start_ZC_SerialRangeCheck = 1;
        consensus.height_start_ZC_SerialsV2 = 201;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // validation by-pass
        consensus.nPctmBadBlockTime = 1489001494; // Skip nBit validation of Block 201 per PR #915
        consensus.nPctmBadBlockBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1577169743; // 10 minutes after genesis
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xdf;
        pchMessageStart[2] = 0x90;
        pchMessageStart[3] = 0x94;
        nDefaultPort = 12124;

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("pactumcoin.com", "testnet.seed.pactumcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 120); // Testnet pctm addresses start with 'q'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet pctm script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pctm BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container < std::vector < unsigned char > > ();
        // Testnet pctm BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container < std::vector < unsigned char > > ();
        // Testnet pctm BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container < std::vector < unsigned char > > ();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1577169143, 454267, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000005350f609d8dee013062226f9459d859d95db8023623b8c22b07a322e565"));
        assert(genesis.hashMerkleRoot == uint256S("0x3a2353b4f74192b56cc2cfbbfe49796948f47cece1b9ea3278fd11aed287b4d1"));

        consensus.nPremineAmount = 100000 * COIN;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 20;   // PCTM starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMasternodeCollateral = 100000 * COIN;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest:
        WIF private key: 922j9RFcqAHmgJNVbTWTYBmoyjs3PWnbsqRpXoqvHSQGpNGfwJo
        private key hex: 3a9ad8c623dcdd9154cf0e653ccf364f535ff5caacb20dc5ac2ebffe9fbb1b72
        Address: qeQ7VKrCFzV5pRCNwUwYyxF1g9c51jmKrG
        */
        consensus.strSporkPubKey = "04f3ba07d257c6b280a66b8b181c5eae07004b1b280b2251b84953bd916f61213f0dbd35e1607a83b1c9ff73000e2718a2dbebdea2ec6dba1f0f4b16439e0b2a41";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
        consensus.height_last_PoW = 250;
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_BIP65 = 851019;              // Not defined for regtest. Inherit TestNet value.
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_MessSignaturesV2 = 1;
        consensus.height_start_StakeModifierNewSelection = 0;
        consensus.height_start_StakeModifierV2 = 251;       // start with modifier V2 on regtest
        consensus.height_start_TimeProtoV2 = 999999999;
        consensus.height_start_ZC = 300;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_PublicSpends = 400;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_start_ZC_SerialsV2 = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0;                 // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply = 0;


        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 12126;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
