INF = 10 ** 9


class CrossingLines(object):
    def __init__(self):
        self.lines = []

    def add_line(self, current, derivative):
        self.lines.append((current, derivative))

    def get_min(self, time):
        # Process the passage of time
        return len(self.lines) + time  # nonsense


class Row(object):
    def __init__(self, n, K):
        self.n = n
        self.K = K
        self.time = 0
        self.obstacles = []  # Must be read from the parent structure
        self.segment_tree = [CrossingLines()] * (4 * n)
        self.init_tree(1, 0, n)

    def tik_tok(self):
        self.time += 1
        if self.time % self.K == 0:
            # reconstruct
            return

    def query_tree(self, x, s, e, l, r):
        if r <= s or e <= l:
            return INF
        if l <= e and s <= r:
            return self.segment_tree[x].get_min(self.time)
        m = int((s + e) / 2)
        return min(self.query_tree(2 * x, s, m, l, r),
                   self.query_tree(2 * x + 1, m, e, l, r))

    def min_query(self):
        best = INF
        ptr = 0
        for obstacle in self.obstacles:
            best = min(best, self.query_tree(1, 0, self.n, ptr, obstacle))
            ptr = obstacle + 1
        best = min(best, self.query_tree(1, 0, self.n, ptr, self.n))
        return best

    def init_tree(self, x, s, e):
        if e - s < 2:
            # self.segment_tree[x].add_line()
            return
        m = int((s + e) / 2)
        self.init_tree(2 * x, s, m)
        self.init_tree(2 * x + 1, m, e)
