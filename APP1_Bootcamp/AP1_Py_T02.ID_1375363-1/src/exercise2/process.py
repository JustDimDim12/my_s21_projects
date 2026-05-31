import asyncio
import os
import requests

from url import URL

def is_path(path): #проверка пути
    if not os.path.isdir(path):
        print('Некорректный путь')
        return 0
    if not os.access(path, os.W_OK):
        print('Нет прав на запись')
        return 0
    return path

async def get_path(): #получение пути
    path = await asyncio.to_thread(input)
    path = is_path(path)
    while not path:
        path = await asyncio.to_thread(input, "Введите иной путь: ")
        path = is_path(path)
    return path

async def downloading(url, path): #загрузка изображений
    try:
        response = await asyncio.to_thread(requests.get, url.url, timeout=10)
    except:
        url.status = 'Ошибка'
        return

    content_type = response.headers.get('Content-Type', '')

    if not content_type.startswith('image/'):
        url.status = 'Ошибка'
        return

    if response.status_code == 200:
        os.makedirs(path, exist_ok=True)
        file_path = f'{path}/{url.filename}'
        with open(file_path, 'wb') as f:
            f.write(response.content)
        url.status = 'Успех'
    else:
        url.status = 'Ошибка'

async def get_url(path): #получение url-ов
    urls = []

    while True:
        url = URL(await asyncio.to_thread(input))
        if not url.url.strip():
            if len(urls) == 0:
                urls.append(URL('-'))
            break
        else:
            url.task = asyncio.create_task(downloading(url, path))
            urls.append(url)

    if urls:
        while any(not url.task.done() for url in urls):
            print(f'\rИдёт загрузка изображений...', end='', flush=True)
            await asyncio.sleep(0.01)
        print('\rЗагрузка завершена!                  ')

    return urls

async def process(): #запуск процесса
    path = await get_path()
    urls = await get_url(path)
    return urls

def final(urls): #таблица итогов
    data = [("Ссылка", "Статус")] + [(url.url, url.status) for url in urls]

    w1 = max(len(item[0]) for item in data)
    w2 = max(len(item[1]) for item in data)

    border = f"+-{'-' * w1}-+-{'-' * w2}-+"

    output = [border]

    for i, (col1, col2) in enumerate(data):
        output.append(f"| {col1:<{w1}} | {col2:<{w2}} |")
        if i == 0:
            output.append(border)

    output.append(border)
    return output
