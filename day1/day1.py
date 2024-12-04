import fileinput


def main():
    l1 = []
    l2 = []
    with open("test.txt", "r") as file:
        for line in file:
            numbers = line.split("   ")
            l1.append(numbers[0].strip())
            l2.append(numbers[1].strip())
    l1.sort()
    l2.sort()
    similarityScore = 0
    for i in range(len(l1)):
        currentNumber = l1[i]
        similiarityOccurence = l2.count(currentNumber)
        similarityScore += int(l1[i]) * similiarityOccurence

    print(similarityScore)
    return similarityScore

if __name__ == "__main__":
    main()
