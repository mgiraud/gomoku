#ifndef PLAYER_HPP
# define PLAYER_HPP

# define OPPONENT(X) (X) == (P_BLACK) ? (P_WHITE) : (P_BLACK)

typedef enum 	e_player_color {
	P_BLACK = 0,
	P_WHITE
}				t_player_color;

typedef enum 	e_player_type {
	P_PLAYER = 0,
	P_AI
}				t_player_type;

class Player {

public:
	t_player_color	color;
	t_player_type	type;

	Player(t_player_color color, t_player_type type);
	~Player(void);
};
#endif
