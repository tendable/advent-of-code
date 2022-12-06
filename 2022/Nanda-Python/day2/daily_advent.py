shapes = {
    "A": "rock",
    "B": "paper",
    "C": "scissor",
    "X": "rock",
    "Y": "paper",
    "Z": "scissor",
    "rock": 1,
    "paper": 2,
    "scissor": 3
}


def determine_winner(opponent, me):
    if opponent == "rock" and me == "rock":
        return "deuce"
    elif opponent == "rock" and me == "paper":
        return "me"
    elif opponent == "rock" and me == "scissor":
        return "opponent"
    elif opponent == "paper" and me == "rock":
        return "opponent"
    elif opponent == "paper" and me == "paper":
        return "deuce"
    elif opponent == "paper" and me == "scissor":
        return "me"
    elif opponent == "scissor" and me == "rock":
        return "me"
    elif opponent == "scissor" and me == "paper":
        return "opponent"
    elif opponent == "scissor" and me == "scissor":
        return "deuce"


def get_points_for_shape(selected_shape):
    key = shapes[selected_shape]
    return shapes[key]


def choose_shape_strategy(opponent_chosen_shape, my_strategy_shape):
    if opponent_chosen_shape == "A" and my_strategy_shape == "X":
        # need to lose - returning scissor
        return "Z"
    elif opponent_chosen_shape == "A" and my_strategy_shape == "Y":
        # need to draw - returning rock
        return "X"
    elif opponent_chosen_shape == "A" and my_strategy_shape == "Z":
        # need to win - returning paper
        return "Y"
    elif opponent_chosen_shape == "B" and my_strategy_shape == "X":
        # need to lose - returning rock
        return "X"
    elif opponent_chosen_shape == "B" and my_strategy_shape == "Y":
        # need to draw - returning paper
        return "Y"
    elif opponent_chosen_shape == "B" and my_strategy_shape == "Z":
        # need to win - returning scissor
        return "Z"
    elif opponent_chosen_shape == "C" and my_strategy_shape == "X":
        # need to lose - returning paper
        return "Y"
    elif opponent_chosen_shape == "C" and my_strategy_shape == "Y":
        # need to draw - returning scissor
        return "Z"
    elif opponent_chosen_shape == "C" and my_strategy_shape == "Z":
        # need to win - returning rock
        return "X"


def calculate_points(game_winner, my_chosen_shape):
    total_points = 0
    if game_winner == "me":
        points_for_winning = 6
        shape_points = get_points_for_shape(my_chosen_shape)
        total_points = points_for_winning + shape_points
    elif game_winner == "deuce":
        points_for_draw = 3
        shape_points = get_points_for_shape(my_chosen_shape)
        total_points = points_for_draw + shape_points
    elif game_winner == "opponent":
        points_for_losing = 0
        shape_points = get_points_for_shape(my_chosen_shape)
        total_points = points_for_losing + shape_points

    return total_points


def run_part2():
    input_file = "./day2/day2.input"
    total_game_points = 0
    with open(input_file, 'r') as f:
        for game in f:
            oppo, i = game.strip().split(" ")
            selected_shape = choose_shape_strategy(oppo, i)
            game_winner = determine_winner(shapes[oppo], shapes[selected_shape])
            total_game_points = total_game_points + calculate_points(game_winner, selected_shape)

    print('\tMy Total Points (New Strategy): {0}'.format(total_game_points))


def run():
    print("Advent Day 2 - Part 1 & 2")
    input_file = "./day2/day2.input"
    my_total_points_across_all_games = 0

    with open(input_file, 'r') as f:
        for game in f:
            oppo, i = game.strip().split(" ")
            game_winner = determine_winner(shapes[oppo], shapes[i])
            my_total_points_across_all_games = my_total_points_across_all_games + calculate_points(game_winner, i)

    print('\tMy Total Points: {0}'.format(my_total_points_across_all_games))
    run_part2()
