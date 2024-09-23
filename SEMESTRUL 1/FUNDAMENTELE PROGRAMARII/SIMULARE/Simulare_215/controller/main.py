from repository.repoObiecte import RepoObiecte
from service.objectService import ObjectService
from UI.UI import UI

fileName = "/Users/danpetri/Documents/IT/personal_projects/PYTHON/Simulare/data/obiecte.txt"
rep = RepoObiecte(fileName)
srv = ObjectService(rep)
ui = UI(srv)
ui.startUI()