from colorama import Fore, Style


def exception_fn():
    try:
        s = input("n=")
        s = int(s)
        print('This is printed after the conversion.')
    except ValueError:
        print(Fore.RED+"ERROR"+Style.RESET_ALL)
        #assert False

    print('This is printed after the try-except block.')

exception_fn()
