
#include "npcstats.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

ESM::NpcStats::Faction::Faction() : mExpelled (false), mRank (-1), mReputation (0) {}

void ESM::NpcStats::load (ESMReader &esm)
{
    while (esm.isNextSub ("FACT"))
    {
        std::string id = esm.getHString();

        Faction faction;

        int expelled = 0;
        esm.getHNOT (expelled, "FAEX");

        if (expelled)
            faction.mExpelled = true;

        esm.getHNOT (faction.mRank, "FARA");

        esm.getHNOT (faction.mReputation, "FARE");

        mFactions.insert (std::make_pair (id, faction));
    }

    mDisposition = 0;
    esm.getHNOT (mDisposition, "DISP");

    for (int i=0; i<27; ++i)
    {
        mSkills[i].mRegular.load (esm);
        mSkills[i].mWerewolf.load (esm);
    }

    bool hasWerewolfAttributes = false;
    esm.getHNOT (hasWerewolfAttributes, "HWAT");

    if (hasWerewolfAttributes)
    {
        for (int i=0; i<8; ++i)
            mWerewolfAttributes[i].load (esm);
    }

    mIsWerewolf = false;
    esm.getHNOT (mIsWerewolf, "WOLF");

    mBounty = 0;
    esm.getHNOT (mBounty, "BOUN");

    mReputation = 0;
    esm.getHNOT (mReputation, "REPU");

    mWerewolfKills = 0;
    esm.getHNOT (mWerewolfKills, "WKIL");

    // No longer used
    if (esm.isNextSub("PROF"))
        esm.skipHSub(); // int profit

    // No longer used. Now part of CreatureStats.
    if (esm.isNextSub("ASTR"))
        esm.skipHSub(); // attackStrength

    mLevelProgress = 0;
    esm.getHNOT (mLevelProgress, "LPRO");

    esm.getHNT (mSkillIncrease, "INCR");

    while (esm.isNextSub ("USED"))
        mUsedIds.push_back (esm.getHString());

    mTimeToStartDrowning = 0;
    esm.getHNOT (mTimeToStartDrowning, "DRTI");

    // No longer used
    float lastDrowningHit = 0;
    esm.getHNOT (lastDrowningHit, "DRLH");

    // No longer used
    float levelHealthBonus = 0;
    esm.getHNOT (levelHealthBonus, "LVLH");

    mCrimeId = -1;
    esm.getHNOT (mCrimeId, "CRID");
}

void ESM::NpcStats::save (ESMWriter &esm) const
{
    for (std::map<std::string, Faction>::const_iterator iter (mFactions.begin());
        iter!=mFactions.end(); ++iter)
    {
        esm.writeHNString ("FACT", iter->first);

        if (iter->second.mExpelled)
        {
            int expelled = 1;
            esm.writeHNT ("FAEX", expelled);
        }

        if (iter->second.mRank >= 0)
            esm.writeHNT ("FARA", iter->second.mRank);

        if (iter->second.mReputation)
            esm.writeHNT ("FARE", iter->second.mReputation);
    }

    if (mDisposition)
        esm.writeHNT ("DISP", mDisposition);

    for (int i=0; i<27; ++i)
    {
        mSkills[i].mRegular.save (esm);
        mSkills[i].mWerewolf.save (esm);
    }

    esm.writeHNT ("HWAT", true);
    for (int i=0; i<8; ++i)
        mWerewolfAttributes[i].save (esm);

    if (mIsWerewolf)
        esm.writeHNT ("WOLF", mIsWerewolf);

    if (mBounty)
        esm.writeHNT ("BOUN", mBounty);

    if (mReputation)
        esm.writeHNT ("REPU", mReputation);

    if (mWerewolfKills)
        esm.writeHNT ("WKIL", mWerewolfKills);

    if (mLevelProgress)
        esm.writeHNT ("LPRO", mLevelProgress);

    esm.writeHNT ("INCR", mSkillIncrease);

    for (std::vector<std::string>::const_iterator iter (mUsedIds.begin()); iter!=mUsedIds.end();
        ++iter)
        esm.writeHNString ("USED", *iter);

    if (mTimeToStartDrowning)
        esm.writeHNT ("DRTI", mTimeToStartDrowning);

    if (mCrimeId != -1)
        esm.writeHNT ("CRID", mCrimeId);
}

void ESM::NpcStats::blank()
{
    mIsWerewolf = false;
    mDisposition = 0;
    mBounty = 0;
    mReputation = 0;
    mWerewolfKills = 0;
    mLevelProgress = 0;
    for (int i=0; i<8; ++i)
        mSkillIncrease[i] = 0;
    mTimeToStartDrowning = 20;
    mCrimeId = -1;
}
