import pulp
import sys

def solve(buttons: list[list[int]], joltage: list[int]) -> int:
    problem = pulp.LpProblem("Factory", pulp.LpMinimize)
    x = [
        pulp.LpVariable(f"x_{i}", lowBound=0, cat="Integer")
        for i in range(len(buttons))
    ]
    problem += pulp.lpSum(x)
    for j in range(len(joltage)):
        problem += (
            pulp.lpSum(
                x[i]
                for i in range(len(buttons))
                if j in buttons[i]
            ) == joltage[j]
        )
    problem.solve(pulp.PULP_CBC_CMD(msg=False))
    solution = [x_.varValue for x_ in x]
    for j in range(len(joltage)):
        joltage_sum = 0
        for b in range(len(buttons)):
            if j in buttons[b]:
                joltage_sum += solution[b]
        if joltage_sum < joltage[j]:
            raise RuntimeError("wrong solution")
    return sum(solution)

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