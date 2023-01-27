import csv
import sys

# define the main function


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # Create list of dicts to read data from file
    data = []
    # Read Data from the file
    d = open(sys.argv[1], "r")
    reader = csv.DictReader(d)
    for row in reader:
        name = row['name']
        AGATC = int(row['AGATC'])
        AATG = int(row['AATG'])
        TATC = int(row['TATC'])
        # append dicts to the list
        data.append({'name': name, 'AGATC': AGATC, 'AATG': AATG, 'TATC': TATC})

    # Get the how many every STR repeated using str_count function
    agatc = str_count(sys.argv[2], "AGATC")
    aatg = str_count(sys.argv[2], "AATG")
    tatc = str_count(sys.argv[2], "TATC")

    # check for the values in the data base and print the result
    x = 0
    length = len(data)
    for i in range(0, length):
        if data[i]['AGATC'] == agatc and data[i]['AATG'] == aatg and data[i]['TATC'] == tatc:
            print(f"{data[i]['name']}")
            return
        else:
            x += 1
    # if no match print this out
    if x >= length:
        print("No match")
        return


# define STR counter function for sequence file
def str_count(file, STR):
    # Read the data  from the sequance file
    sequence = open(file, "r")
    seq = sequence.read()
    # slice the sequence and compare it to the STR, Count how many times it repeated
    i = 0
    count = 0
    chain_l = 0
    x = len(STR)
    # scan over the sequnce slice by slice
    # check every position
    for i in range(len(seq)):
        # find a STR, count the repeat
        if seq[i: i + x] == STR:
            l = i
            j = i + x
            while seq[l: j] == STR:
                count += 1
                l += x
                j += x
            # save the longest run, set the counter = 0
            chain_l = max(chain_l, count)
            count = 0
    # Return chain_l
    return chain_l
    seq.close()


# Call the main function
if __name__ == '__main__':
    main()

