import sys

from z3 import Int, Optimize, Sum

def solve(buttons: list[list[int]], joltage: list[int]) -> int:
    x = [Int(f"x_{i}") for i in range(len(buttons))]
    opt = Optimize()
    opt.add([
        x[i] >= 0
        for i in range(len(buttons))
    ])
    opt.add([
        sum(
            x[i]
            for i in range(len(buttons))
            if j in buttons[i]
        ) == joltage[j]
        for j in range(len(joltage))
    ])
    objective = Sum(x)
    opt.minimize(objective)
    
    opt.check()
    model = opt.model()
    return model.evaluate(objective).as_long()


def main():
    total = 0
    for line in sys.stdin:
        lights, *raw_buttons, raw_joltage = line.split()
        buttons = [
            list(map(int, raw_button[1:-1].split(",")))
            for raw_button in raw_buttons
        ]
        joltage = list(map(int, raw_joltage[1:-1].split(",")))
        total += solve(buttons, joltage)
    print(total)


if __name__ == "__main__":
    main()