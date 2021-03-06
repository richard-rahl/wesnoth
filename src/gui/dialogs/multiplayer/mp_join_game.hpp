/*
   Copyright (C) 2008 - 2018 by the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#pragma once

#include "ai/configuration.hpp"
#include "game_initialization/connect_engine.hpp"
#include "game_initialization/lobby_info.hpp"
#include "game_initialization/multiplayer.hpp"
#include "gui/dialogs/modal_dialog.hpp"
#include "gui/dialogs/multiplayer/player_list_helper.hpp"
#include "gui/dialogs/multiplayer/plugin_executor.hpp"
#include "mp_game_settings.hpp"

class config;

namespace gui2
{

class tree_view_node;

namespace dialogs
{

class mp_join_game : public modal_dialog, private plugin_executor
{
public:
	mp_join_game(saved_game& state, mp::lobby_info& lobby_info, wesnothd_connection& connection,
		const bool first_scenario = true, const bool observe_game = false);

	~mp_join_game();

	bool fetch_game_config();
	bool started() const { return level_["started"].to_bool(); }
private:
	/** Inherited from modal_dialog, implemented by REGISTER_DIALOG. */
	virtual const std::string& window_id() const override;

	/** Inherited from modal_dialog. */
	virtual void pre_show(window& window) override;

	/** Inherited from modal_dialog. */
	virtual void post_show(window& window) override;

	void generate_side_list(window& window);

	void network_handler(window& window);

	config& get_scenario();

	config level_;

	saved_game& state_;

	mp::lobby_info& lobby_info_;

	wesnothd_connection& network_connection_;

	std::size_t update_timer_;

	const bool first_scenario_;

	bool observe_game_;
	bool stop_updates_;

	std::map<std::string, tree_view_node*> team_tree_map_;

	std::unique_ptr<player_list_helper> player_list_;
};

} // namespace dialogs
} // namespace gui2
