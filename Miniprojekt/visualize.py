import matplotlib.pyplot as plt

def parse_lcvrp_file(filename):
    coords = {}
    permutation = []

    with open(filename, "r") as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        line = lines[i].strip()

        if line.startswith("PERMUTATION"):
            permutation = list(map(int, line.split(":")[1].split()))

        elif line == "NODE_COORD_SECTION":
            i += 1
            while not lines[i].strip().startswith("DEMAND_SECTION"):
                parts = lines[i].split()
                node_id = int(parts[0])
                x, y = float(parts[1]), float(parts[2])
                coords[node_id] = (x, y)
                i += 1
            continue

        i += 1

    return coords, permutation


def plot_permutation(coords, permutation):
    plt.figure(figsize=(8, 8))

    for idx, node_id in enumerate(permutation, start=1):
        x, y = coords[node_id]
        plt.scatter(x, y, color="red")
        plt.text(x + 0.5, y + 0.5, str(idx), fontsize=10)

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.axis("equal")
    plt.show()


if __name__ == "__main__":
    filename = "dane/1.lcvrp"  # <- tu podaj nazwę pliku
    coords, permutation = parse_lcvrp_file(filename)
    plot_permutation(coords, permutation)
