import argparse
import importlib

advent_day = 1


def parse_arguments():
    day_parser = argparse.ArgumentParser(prog='advent', usage='%(prog)s [options] day 1',
                                         description="Advent of Code",
                                         formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    day_parser.add_argument("--day", action='store', type=int, help="code for day", required=True)
    args = day_parser.parse_args()
    global advent_day
    advent_day = args.day
    run_advent(advent_day)


def run_advent(day_in_advent):
    module = "day" + str(day_in_advent) + ".daily_advent"
    advent = importlib.import_module(module)
    advent.run()


if __name__ == '__main__':
    parse_arguments()
