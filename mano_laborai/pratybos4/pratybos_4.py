import random
import re

# Šią programą reikės perrašyti su C kalba

def main():

    capacity = int(input("input capacity: "))
    if capacity < 1:
        print('capacity should be greater than zero')
        main()

    raw_array = [0 for x in range(1, capacity+1)]

    print('your template array: ', raw_array)

    size = int(input("input size: "))
    if size < 1:
        print('size should be greater than zero')
        main()

    array = [random.randint(1,9) for x in range(1, size+1)]

    print('your generated array ', array)
    actions(array)


def actions(array):

    action = input('your action: ')

    print(action)

    args = re.sub("[^\w]", " ",  action).split()

    print('len', len(args))
    if 1 < len(args) < 3:
        action_word = args[0]
        pos = int(args[1])
    elif len(args) == 3:
        action_word = args[0]
        pos = int(args[1])
        number = int(args[2])
    else:
        print('wrong number of arguments presented')
        actions(array)


    if action_word == 'delete':
        if pos < len(array):
            array.pop(pos)
            print('your modified array: ', array)
        else:
            print('invalid index')
        actions(array)
    elif action_word == 'update':
        array[pos] = number
        print('your modified array', array)
        actions(array)
    elif action_word == 'insert':
        array.insert(pos, number)
        print('your modified array', array)
        actions(array)
    else:
        print('there is no action %s' %(action_word))
        actions(array)

main()

