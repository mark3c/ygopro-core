/*
 * duel.h
 *
 *  Created on: 2010-4-8
 *      Author: Argon
 */

#ifndef DUEL_H_
#define DUEL_H_

#include "common.h"
#include "mtrandom.h"
#include <set>
#include <unordered_set>

class card;
class group;
class effect;
class field;
class interpreter;

inline void write_buffer_vector(std::vector<byte>& buffer, const void* data, int size) {
	if (size > 0) {
		const auto len = buffer.size();
		buffer.resize(len + size);
		std::memcpy(&buffer[len], data, size);
	}
}

class duel {
public:
	using card_set = std::set<card*, card_sort>;
	char strbuffer[256];
	std::vector<byte> message_buffer;
	interpreter* lua;
	field* game_field;
	mt19937 random;
	std::unordered_set<card*> cards;
	std::unordered_set<card*> assumes;
	std::unordered_set<group*> groups;
	std::unordered_set<group*> sgroups;
	std::unordered_set<effect*> effects;
	std::unordered_set<effect*> uncopy;
	
	duel();
	~duel();
	void clear();
	
	card* new_card(uint32 code);
	group* new_group();
	group* new_group(card* pcard);
	group* new_group(const card_set& cset);
	effect* new_effect();
	void delete_card(card* pcard);
	void delete_group(group* pgroup);
	void delete_effect(effect* peffect);
	void release_script_group();
	void restore_assumes();
	int32 read_buffer(byte* buf);
	void write_buffer(const void* data, int size);
	void write_buffer32(uint32 value);
	void write_buffer16(uint16 value);
	void write_buffer8(uint8 value);
	void clear_buffer();
	void set_responsei(uint32 resp);
	void set_responseb(byte* resp);
	int32 get_next_integer(int32 l, int32 h);
private:
	group* register_group(group* pgroup);
};

#endif /* DUEL_H_ */
