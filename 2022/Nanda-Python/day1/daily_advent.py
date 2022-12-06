import heapq
from operator import itemgetter


def get_top(elfs, number_of_top):
    top_elfs = heapq.nlargest(number_of_top, elfs.items(), key=itemgetter(1))
    return dict(top_elfs)


def run():
    print("Advent Day 1 - Part 1 & 2")
    input_file = "./day1/day1.input"
    calories = 0
    elfs = {}

    with open(input_file, 'r') as f:
        elf_name = "Elf" + str(len(elfs) + 1)
        for line in f:
            line = line.strip()
            if len(line) == 0:
                elfs[elf_name] = calories
                elf_name = "Elf" + str(len(elfs) + 1)
                calories = 0
            else:
                calories = calories + int(line)

        most_calories_being_carried = max(elfs.values())
        elf_carrying_the_most = max(elfs, key=elfs.get)
        print('\tElf: {0} is carrying the maximum calories: {1}'.format(elf_carrying_the_most,
                                                                        most_calories_being_carried))

        top_3_elfs = get_top(elfs, 3)
        print('\tTotal Calories carried by top 3 elfs: {0}'.format(sum(top_3_elfs.values())))
