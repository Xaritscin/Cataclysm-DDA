#ifndef TRAP_H
#define TRAP_H

#include "color.h"
#include "itype.h"
#include "json.h"
#include <string>

class Creature;
class item;

typedef int trap_id;
/** map trap ids to index into <B>traps</B> */
extern std::map<std::string, int> trapmap;

struct trap;

struct trapfunc {
    // creature is the creature that triggered the trap,
    // p is the point where the trap is (not where the creature is)
    // creature can be NULL.
    void none           ( Creature *, int, int ) { };
    void bubble         ( Creature *creature, int x, int y );
    void cot            ( Creature *creature, int x, int y );
    void beartrap       ( Creature *creature, int x, int y );
    void snare_light    ( Creature *creature, int x, int y );
    void snare_heavy    ( Creature *creature, int x, int y );
    void board          ( Creature *creature, int x, int y );
    void caltrops       ( Creature *creature, int x, int y );
    void tripwire       ( Creature *creature, int x, int y );
    void crossbow       ( Creature *creature, int x, int y );
    void shotgun        ( Creature *creature, int x, int y );
    void blade          ( Creature *creature, int x, int y );
    void landmine       ( Creature *creature, int x, int y );
    void telepad        ( Creature *creature, int x, int y );
    void goo            ( Creature *creature, int x, int y );
    void dissector      ( Creature *creature, int x, int y );
    void sinkhole       ( Creature *creature, int x, int y );
    void pit            ( Creature *creature, int x, int y );
    void pit_spikes     ( Creature *creature, int x, int y );
    void pit_glass      ( Creature *creature, int x, int y );
    void lava           ( Creature *creature, int x, int y );
    void portal         ( Creature *creature, int x, int y );
    void ledge          ( Creature *creature, int x, int y );
    void boobytrap      ( Creature *creature, int x, int y );
    void temple_flood   ( Creature *creature, int x, int y );
    void temple_toggle  ( Creature *creature, int x, int y );
    void glow           ( Creature *creature, int x, int y );
    void hum            ( Creature *creature, int x, int y );
    void shadow         ( Creature *creature, int x, int y );
    void drain          ( Creature *creature, int x, int y );
    void snake          ( Creature *creature, int x, int y );
};

typedef void (trapfunc::*trap_function)( Creature *, int x, int y );

struct trap {
        std::string id;
        int loadid;
        long sym;
        nc_color color;
        std::string name;
    private:
        int visibility; // 1 to ??, affects detection
        int avoidance;  // 0 to ??, affects avoidance
        int difficulty; // 0 to ??, difficulty of assembly & disassembly
        bool benign = false;
        trap_function act;
        /**
         * If an item with this weight or more is thrown onto the trap, it triggers.
         */
        int trigger_weight;
        int funnel_radius_mm;
    public:
        std::vector<itype_id> components; // For disassembly?

        int get_visibility() const
        {
            return visibility;
        }
        int get_avoidance() const
        {
            return avoidance;
        }
        int get_difficulty() const
        {
            return difficulty;
        }
        // Type of trap
        bool is_benign() const
        {
            return benign;
        }
        bool is_funnel() const;
        /** Player has not yet seen the trap and returns the variable chance, at this moment,
         of whether the trap is seen or not. */
        bool detect_trap( const tripoint &pos, const player &p ) const;
        /** Can player/npc p see this kind of trap given their memory? */
        bool can_see( const tripoint &pos, const player &p ) const;
        /** Trigger trap effects by creature that stepped onto it. */
        void trigger( const tripoint &pos, Creature *creature ) const;
        /**
         * If the given item is throw onto the trap, does it trigger the trap?
         */
        bool triggered_by_item( const item &itm ) const;

        double funnel_turns_per_charge( double rain_depth_mm_per_hour ) const;
        /* pending jsonize
        std::set<std::string> flags
        std::string id;
        */

        /**
         * Whether this is the null-traps, aka no trap at all.
         */
        bool is_null() const;
        /**
         * Loads the trap and adds it to the @ref trapmap, and the @ref traplist.
         * @throw std::string if the json is invalid as usual.
         */
        static void load( JsonObject &jo );
        /**
         * Releases the loaded trap objects in @ref trapmap and @ref traplist.
         */
        static void reset();
        /**
         * Stores the actual @ref loadid of the loaded traps in the global tr_* variables.
         * It also sets the trap ids of the terrain types that have build-in traps.
         * Must be called after all traps have been loaded.
         */
        static void finalize();
};

/** list of all trap types */
extern std::vector<trap *> traplist;

trap_function trap_function_from_string(std::string function_name);

extern trap_id
tr_null,
tr_bubblewrap,
tr_cot,
tr_brazier,
tr_funnel,
tr_makeshift_funnel,
tr_leather_funnel,
tr_rollmat,
tr_fur_rollmat,
tr_beartrap,
tr_beartrap_buried,
tr_nailboard,
tr_caltrops,
tr_tripwire,
tr_crossbow,
tr_shotgun_2,
tr_shotgun_1,
tr_engine,
tr_blade,
tr_light_snare,
tr_heavy_snare,
tr_landmine,
tr_landmine_buried,
tr_telepad,
tr_goo,
tr_dissector,
tr_sinkhole,
tr_pit,
tr_spike_pit,
tr_glass_pit,
tr_lava,
tr_portal,
tr_ledge,
tr_boobytrap,
tr_temple_flood,
tr_temple_toggle,
tr_glow,
tr_hum,
tr_shadow,
tr_drain,
tr_snake;

#endif
