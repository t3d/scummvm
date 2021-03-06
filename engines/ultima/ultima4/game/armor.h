/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ULTIMA4_GAME_ARMOR_H
#define ULTIMA4_GAME_ARMOR_H

#include "ultima/ultima4/filesys/savegame.h"
#include "ultima/shared/std/containers.h"
#include "ultima/shared/std/string.h"

namespace Ultima {
namespace Ultima4 {

class ConfigElement;

class Armor {
public:
	typedef Common::String string;

	/**
	 * Returns armor by ArmorType.
	 */
	static const Armor *get(ArmorType a);

	/**
	 * Returns armor that has the given name
	 */
	static const Armor *get(const string &name);

	// Getters
	ArmorType getType() const       {
		return _type;      /**< Returns the ArmorType of the armor */
	}
	const string &getName() const   {
		return _name;      /**< Returns the name of the armor */
	}
	int getDefense() const          {
		return _defense;   /**< Returns the defense value of the armor */
	}
	/** Returns true if the class given can wear the armor */
	bool canWear(ClassType klass) const {
		return _canUse & (1 << klass);
	}

private:
	Armor(const ConfigElement &conf);

	static void loadConf();
	static bool _confLoaded;
	static Std::vector<Armor *> _armors;

	ArmorType _type;
	string _name;
	unsigned char _canUse;
	int _defense;
	unsigned short _mask;
};

} // End of namespace Ultima4
} // End of namespace Ultima

#endif
