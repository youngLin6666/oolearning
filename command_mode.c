#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 命令接口（抽象命令）
typedef struct Command {
	void (*execute)(void* receiver);  // 执行方法
	void (*undo)(void* receiver);     // 撤销方法
} Command;

//调用者 : 命令控制器
typedef struct CommandController {
	Command* commands[10];
	int slot_count;
} CommandController;

void controller_init(CommandController* ctrl) {
	ctrl->slot_count = 0;
}

void  controller_set_command(CommandController* ctrl, Command* cmd, int slot) {
	if(slot >=0 && slot < 10) {
		ctrl->commands[slot] = cmd;
	}
}

void controller_execute_all(CommandController* ctrl) {
	for(int i = 0; i < ctrl->slot_count; i++) {
		ctrl->commands[i]->execute(ctrl->commands[i]);
	}
}

void controller_undo_last(CommandController* ctrl) {
	if(ctrl->slot_count > 0) {
		ctrl->commands[ctrl->slot_count - 1]->undo(ctrl->commands[ctrl->slot_count - 1]);
		ctrl->slot_count--;
	}
}

//接收者 : 灯设备
typedef struct Light {
	int is_on;
} Light;

void light_on(Light * lig) {
	lig->is_on = 1;
}

void light_off(Light * lig) {
	lig->is_on = 0;
}

//具体命令 : 灯的开关
typedef struct LightCommand {
	Command base;
	Light *light;
	int previous_state;
} LightCommand;

void light_command_execute(void *receiver) {
	LightCommand* cmd = (LightCommand*)receiver;
	Light* light = cmd->light;
	light_on(light);
}

void light_command_undo(void* receiver) {
	LightCommand* cmd = (LightCommand*)receiver;
	Light* light = cmd->light;
	if(cmd->previous_state) {
		light_off(light);

	} else {
		light_on(light);
	}
}

//接收者 : CD机
typedef struct CDPlayer {
	int is_playing;
	int volume;
} CDPlayer;

void cd_player_volume_turn_up(CDPlayer *player, int up_num) {
	player->volume += up_num;
	printf("up volume(%d)\n", player->volume);
}

void cd_player_volume_turn_down(CDPlayer *player, int dw_num) {
	if(player->volume > dw_num) {
		player->volume -= dw_num;

	} else {
		player->volume = 0;	
	}

	printf("down volume(%d)\n", player->volume);
}

void cd_player_volume_set(CDPlayer *player, int set_num) {
	if(set_num >= 0) {
		player->volume = set_num;
	}

	printf("set volume(%d)\n", player->volume);
}

void cd_player_play(CDPlayer *player) {
	player->is_playing = 1;
	printf("CD is playing\n");
}

void cd_player_stop(CDPlayer *player) {
	player->is_playing = 0;
	printf("CD is stopping\n");
}

//具体命令 : CD Player的控制
typedef struct CDCommand {
	Command base;
	CDPlayer *player;
	int previous_state;
	int previous_volume;
} CDCommand;

void cd_player_command_execute(void *receiver) {
	CDCommand *cmd = (CDCommand *)receiver;
	CDPlayer *player = cmd->player;

	cd_player_volume_set(player, 3);
	cd_player_play(player);
	cd_player_volume_turn_up(player, 10);
	cd_player_volume_turn_down(player, 2);
	cd_player_volume_turn_down(player, 29);
}

void cd_player_command_undo(void* receiver) {
	CDCommand *cdcmd = (CDCommand*)receiver;
	CDPlayer *player = cdcmd->player;

	if (cdcmd->previous_state) {
		cd_player_stop(player);
	} else {
		cd_player_play(player);
	}

	cd_player_volume_set(player, cdcmd->previous_volume);
}

int main(void) {
	CommandController ctrl = {0};
	Light light = {0};
	CDPlayer player = {0};

	LightCommand light_on_cmd = {
		.base.execute = light_command_execute,
		.base.undo = light_command_undo,
		.light = &light
	};

	CDCommand cd_play_cmd = {
		.base.execute = cd_player_command_execute,
		.base.undo = cd_player_command_undo,
		.player = &player
	 };

	controller_set_command(&ctrl, (Command*)&light_on_cmd, 0);
	controller_set_command(&ctrl, (Command*)&cd_play_cmd, 1);
	ctrl.slot_count= 2;

	printf("Executing commands:\n");
	controller_execute_all(&ctrl);

	printf("Executing commands again:\n");
	controller_execute_all(&ctrl);

	printf("\nUndo last command:\n");
	controller_undo_last(&ctrl);

	return 0;
}
