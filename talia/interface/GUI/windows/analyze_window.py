from PyQt6.QtWidgets import QWidget

class AnalyzeWindow(QWidget):
    
    def __init__(self, app):
        super().__init__()
        self.app = app
        
        self.setWindowTitle("Analyze")