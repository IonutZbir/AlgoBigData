class QuickFindUF:
    def __init__(self, n):
        # Ogni elemento inizialmente appartiene a un proprio insieme
        self.id = [i for i in range(n)]

    def find(self, p):
        # Trova l'identificativo dell'insieme a cui appartiene p
        return self.id[p]

    def union(self, p, q):
        # Trova gli identificativi degli insiemi di p e q
        pid = self.find(p)
        qid = self.find(q)

        # Se sono già nello stesso insieme, non fare nulla
        if pid == qid:
            return

        # Cambia tutti gli elementi dell'insieme di p in quello di q
        for i in range(len(self.id)):
            if self.id[i] == pid:
                self.id[i] = qid

# [0, 1, 2, 3, 4, 5, 6]

# union(0, 1)
# union(2, 3)
# [0, 0, 2, 2, 4, 5, 6]