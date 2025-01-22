class GestioneDataset:
    def __init__(self, path):
        self.path = path
        self.gestioneStatistiche = Statistiche()
        self.gestioneExcel = Excel()
    
    def convertiInExcel(self):
        dati = self.gestioneStatistiche.categorie()
        self.gestioneExcel.writeToExcel(dati)
        