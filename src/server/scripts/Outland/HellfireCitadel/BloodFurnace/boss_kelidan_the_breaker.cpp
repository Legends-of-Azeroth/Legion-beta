/*
 *###############################################################################
 *#                                                                             #
 *# Copyright (C) 2022 Project Nighthold <https://github.com/ProjectNighthold>  #
 *#                                                                             #
 *# This file is free software; as a special exception the author gives         #
 *# unlimited permission to copy and/or distribute it, with or without          #
 *# modifications, as long as this notice is preserved.                         #
 *#                                                                             #
 *# This program is distributed in the hope that it will be useful, but         #
 *# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      #
 *# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    #
 *#                                                                             #
 *# Read the THANKS file on the source root directory for more info.            #
 *#                                                                             #
 *###############################################################################
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuras.h"
#include "blood_furnace.h"

enum Kelidan
{
    SAY_WAKE                    = 0,
    SAY_ADD_AGGRO               = 1,
    SAY_KILL                    = 2,
    SAY_NOVA                    = 3,
    SAY_DIE                     = 4,

    SPELL_CORRUPTION            = 30938,
    SPELL_EVOCATION             = 30935,

    SPELL_FIRE_NOVA             = 33132,
    H_SPELL_FIRE_NOVA           = 37371,

    SPELL_SHADOW_BOLT_VOLLEY    = 28599,
    H_SPELL_SHADOW_BOLT_VOLLEY  = 40070,

    SPELL_BURNING_NOVA          = 30940,
    SPELL_VORTEX                = 37370,

    ENTRY_KELIDAN               = 17377,
    ENTRY_CHANNELER             = 17653,

    ACTION_ACTIVATE_ADDS        = 92
};

const float ShadowmoonChannelers[5][4]=
{
    {302.0f, -87.0f, -24.4f, 0.157f},
    {321.0f, -63.5f, -24.6f, 4.887f},
    {346.0f, -74.5f, -24.6f, 3.595f},
    {344.0f, -103.5f, -24.5f, 2.356f},
    {316.0f, -109.0f, -24.6f, 1.257f}
};

class boss_kelidan_the_breaker : public CreatureScript
{
    public:
        boss_kelidan_the_breaker() : CreatureScript("boss_kelidan_the_breaker") { }

        struct boss_kelidan_the_breakerAI : public BossAI
        {
            boss_kelidan_the_breakerAI(Creature* creature) : BossAI(creature, DATA_KELIDAN_THE_BREAKER)
            {
                for (uint8 i = 0; i < 5; ++i)
                    Channelers[i].Clear();
            }

            uint32 ShadowVolley_Timer;
            uint32 BurningNova_Timer;
            uint32 Firenova_Timer;
            uint32 Corruption_Timer;
            uint32 check_Timer;
            bool Firenova;
            bool addYell;
            ObjectGuid Channelers[5];

            void Reset()
            {
                _Reset();
                ShadowVolley_Timer = 1000;
                BurningNova_Timer = 15000;
                Corruption_Timer = 5000;
                check_Timer = 0;
                Firenova = false;
                addYell = false;
                SummonChannelers();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
            }

            void EnterCombat(Unit* who)
            {
                _EnterCombat();
                Talk(SAY_WAKE);
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(true);
                DoStartMovement(who);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                if (rand()%2)
                    return;

                Talk(SAY_KILL);
            }

            void ChannelerEngaged(Unit* who)
            {
                if (who && !addYell)
                {
                    addYell = true;
                    Talk(SAY_ADD_AGGRO);
                }
                for (uint8 i=0; i<5; ++i)
                {
                    Creature* channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                    if (who && channeler && !channeler->isInCombat())
                        channeler->AI()->AttackStart(who);
                }
            }

            void ChannelerDied(Unit* killer)
            {
                for (uint8 i=0; i<5; ++i)
                {
                    Creature* channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                    if (channeler && channeler->isAlive())
                        return;
                }
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
                if (killer)
                    AttackStart(killer);
            }

            ObjectGuid GetChanneled(Creature* channeler1)
            {
                SummonChannelers();
                if (!channeler1)
                    return ObjectGuid::Empty;

                uint8 i;
                for (i=0; i<5; ++i)
                {
                    Creature* channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                    if (channeler && channeler->GetGUID() == channeler1->GetGUID())
                        break;
                }
                return Channelers[(i+2)%5];
            }

            void SummonChannelers()
            {
                for (uint8 i=0; i<5; ++i)
                {
                    Creature* channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                    if (!channeler || channeler->isDead())
                        channeler = me->SummonCreature(ENTRY_CHANNELER, ShadowmoonChannelers[i][0], ShadowmoonChannelers[i][1], ShadowmoonChannelers[i][2], ShadowmoonChannelers[i][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 300000);
                    if (channeler)
                        Channelers[i] = channeler->GetGUID();
                    else
                        Channelers[i].Clear();
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DIE);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                {
                    if (check_Timer <= diff)
                    {
                        if (!me->IsNonMeleeSpellCast(false))
                            DoCast(me, SPELL_EVOCATION);
                        check_Timer = 5000;
                    }
                    else
                        check_Timer -= diff;
                    return;
                }

                if (Firenova)
                {
                    if (Firenova_Timer <= diff)
                    {
                        DoCast(me, SPELL_FIRE_NOVA, true);
                        Firenova = false;
                        ShadowVolley_Timer = 2000;
                    }
                    else
                        Firenova_Timer -=diff;

                    return;
                }

                if (ShadowVolley_Timer <= diff)
                {
                    DoCast(me, SPELL_SHADOW_BOLT_VOLLEY);
                    ShadowVolley_Timer = 5000+rand()%8000;
                }
                else
                    ShadowVolley_Timer -=diff;

                if (Corruption_Timer <= diff)
                {
                    DoCast(me, SPELL_CORRUPTION);
                    Corruption_Timer = 30000+rand()%20000;
                }
                else
                    Corruption_Timer -=diff;

                if (BurningNova_Timer <= diff)
                {
                    if (me->IsNonMeleeSpellCast(false))
                        me->InterruptNonMeleeSpells(true);

                    Talk(SAY_NOVA);

                    if (SpellInfo const* nova = sSpellMgr->GetSpellInfo(SPELL_BURNING_NOVA))
                    {
                        if (Aura* aura = Aura::TryRefreshStackOrCreate(nova, MAX_EFFECT_MASK, me, me))
                            aura->ApplyForTargets();
                    }

                    if (IsHeroic())
                        DoTeleportAll(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());

                    BurningNova_Timer = 20000+rand()%8000;
                    Firenova_Timer= 5000;
                    Firenova = true;
                }
                else
                    BurningNova_Timer -=diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_kelidan_the_breakerAI(creature);
        }
};

/*######
## npc_shadowmoon_channeler
######*/

enum Shadowmoon
{
    SPELL_SHADOW_BOLT       = 12739,
    H_SPELL_SHADOW_BOLT     = 15472,

    SPELL_MARK_OF_SHADOW    = 30937,
    SPELL_CHANNELING        = 39123
};

class npc_shadowmoon_channeler : public CreatureScript
{
    public:

        npc_shadowmoon_channeler() : CreatureScript("npc_shadowmoon_channeler") { }

        struct npc_shadowmoon_channelerAI : public ScriptedAI
        {
            npc_shadowmoon_channelerAI(Creature* creature) : ScriptedAI(creature){ }

            uint32 ShadowBolt_Timer;
            uint32 MarkOfShadow_Timer;
            uint32 check_Timer;

            void Reset()
            {
                ShadowBolt_Timer = 1000+rand()%1000;
                MarkOfShadow_Timer = 5000+rand()%2000;
                check_Timer = 0;
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(true);
            }

            void EnterCombat(Unit* who)
            {
                if (Creature* Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
                    CAST_AI(boss_kelidan_the_breaker::boss_kelidan_the_breakerAI, Kelidan->AI())->ChannelerEngaged(who);
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(true);
                DoStartMovement(who);
            }

            void JustDied(Unit* killer)
            {
               if (Creature* Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
                   CAST_AI(boss_kelidan_the_breaker::boss_kelidan_the_breakerAI, Kelidan->AI())->ChannelerDied(killer);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                {
                    if (check_Timer <= diff)
                    {
                        if (!me->IsNonMeleeSpellCast(false))
                            if (Creature* Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
                            {
                                ObjectGuid channeler = CAST_AI(boss_kelidan_the_breaker::boss_kelidan_the_breakerAI, Kelidan->AI())->GetChanneled(me);
                                if (Unit* channeled = ObjectAccessor::GetUnit(*me, channeler))
                                    DoCast(channeled, SPELL_CHANNELING);
                            }
                        check_Timer = 5000;
                    }
                    else
                        check_Timer -= diff;
                    return;
                }

                if (MarkOfShadow_Timer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_MARK_OF_SHADOW);
                    MarkOfShadow_Timer = 15000+rand()%5000;
                }
                else
                    MarkOfShadow_Timer -=diff;

                if (ShadowBolt_Timer <= diff)
                {
                    DoCastVictim(SPELL_SHADOW_BOLT);
                    ShadowBolt_Timer = 5000+rand()%1000;
                }
                else
                    ShadowBolt_Timer -=diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_shadowmoon_channelerAI(creature);
        }
};

void AddSC_boss_kelidan_the_breaker()
{
    new boss_kelidan_the_breaker();
    new npc_shadowmoon_channeler();
}