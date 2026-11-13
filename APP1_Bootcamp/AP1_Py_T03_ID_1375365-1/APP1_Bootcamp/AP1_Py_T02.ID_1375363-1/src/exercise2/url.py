class URL:
    def __init__(self, url):
        self.url = url
        self.status = ''
        self.filename = url.split('/')[-1]
        self.task = None