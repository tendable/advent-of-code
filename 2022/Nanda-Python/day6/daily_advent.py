def find_marker_values(line):
    communication = []
    communication = line
    pass


def run():
    print("Advent Day 6 - Part 1")
    input_file = "./day6/day6.input"
    total_marker_value = 0
    with open(input_file, 'r') as f:
        for line in f:
            total_marker_value = find_marker_values(line)

    print("Total Marker Value: {0}".format(total_marker_value))
