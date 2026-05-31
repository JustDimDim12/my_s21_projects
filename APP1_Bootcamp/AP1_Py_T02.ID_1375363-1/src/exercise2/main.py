import asyncio

from process import process, final

def main():
    urls = asyncio.run(process())
    res = final(urls)
    print()
    for i in res:
        print(i)

if __name__ == '__main__':
    main()