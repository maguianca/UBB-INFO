package com.example.taximetrie.controller;

import com.example.taximetrie.domeniu.*;
import com.example.taximetrie.events.UtilizatorEntityChangeEvent;
import com.example.taximetrie.observer.Observer;
import com.example.taximetrie.paging.Page;
import com.example.taximetrie.paging.Pageable;
import com.example.taximetrie.service.Service;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SoferController implements Observer<UtilizatorEntityChangeEvent> {

    @FXML
    private TextField minute_field;

    @FXML
    private TableView<Cerere> tabel;

    @FXML
    private TableColumn<Cerere, String> client;

    @FXML
    private TableColumn<Cerere, String> adresa;

    private ObservableList<Cerere> model = FXCollections.observableArrayList();
    private ObservableList<Persoana> modelPersoana = FXCollections.observableArrayList();
    private ObservableList<Comanda> modelComenzi = FXCollections.observableArrayList();

    private Service service;
    private Stage dialogStage;
    private Sofer sofer;
    @FXML
    private TableView<Persoana>table_clienti;
    @FXML
    private TableColumn<Persoana, String>nume;
    @FXML
    private Label label_page;
    @FXML
    private Button prev;
    @FXML
    private Button next;
    Integer currentPage = 1;
    private static final Integer PAGE_SIZE = 2;
    @FXML
    private TableColumn<Comanda,String>nume_client;
    @FXML
    private Label nume_client_fidel;
    @FXML
    private Label media;
    @FXML
    private TableView<Comanda>tabel_comenzi;
    @FXML
    private DatePicker date_picker;


    // Setează serviciul și observatorul
    public void setService(Service service, Stage dialogStage, Sofer sofer) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.sofer = sofer;
        initModel();
        this.service.addObserver(this);
        populatePersonList();

    }

    @FXML
    public void initialize() {
        // Setează coloanele tabelului
        client.setCellValueFactory(cellData -> {
            Long idclient = cellData.getValue().getId_client();
            Persoana persoana = service.getPersoana(idclient);
            return new SimpleStringProperty(persoana != null ? persoana.getNume() : "Necunoscut");
        });
        adresa.setCellValueFactory(new PropertyValueFactory<>("adresa"));
        tabel.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        tabel.setItems(model);
        nume.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getNume()));
        table_clienti.setItems(modelPersoana);
        tabel_comenzi.setItems(modelComenzi);
        nume_client.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getPersoana().getNume()));
    }

    // Inițializează modelul tabelului
    private void initModel() {
        model.clear();
        List<Cerere> allCerere = StreamSupport.stream(service.getCerere().spliterator(), false)
                .collect(Collectors.toList());
        allCerere.forEach(cerere -> System.out.println(cerere.getAdresa()));
        model.setAll(allCerere);
        media.setText(service.media_comenzi(LocalDate.now(),sofer.getId()).toString());
        nume_client_fidel.setText(service.client_fidel(sofer.getId()));
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    // Gestionează acțiunea de acceptare
    public void handleAccept(ActionEvent actionEvent) {
        Cerere cerereSelectata = tabel.getSelectionModel().getSelectedItem();
        if (cerereSelectata == null) {
            showErrorMessage("Te rog să selectezi o cerere din tabel.");
            return;
        }
        String minuteText = minute_field.getText();
        if (minuteText.isEmpty()) {
            showErrorMessage("Te rog să introduci numărul de minute.");
            return;
        }

        try {
            int minute = Integer.parseInt(minuteText);
            if (minute <= 0) {
                showErrorMessage("Numărul de minute trebuie să fie un număr pozitiv.");
                return;
            }

            service.save_oferta(new Oferta(cerereSelectata.getId_client(),sofer.getId(), minute));
            showConfirmationMessage("Oferta a fost trimisa!");
            initModel();

        } catch (NumberFormatException e) {
            showErrorMessage("Numărul de minute trebuie să fie un număr valid.");
        }
    }


    private void showErrorMessage(String message) {

    }

    // Afișează un mesaj de confirmare
    private void showConfirmationMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Confirmare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    public void handle_next(ActionEvent actionEvent) {
        currentPage++;
        populatePersonList();
    }

    public void handle_prev(ActionEvent actionEvent) {
        currentPage--;
        populatePersonList();
    }
    private void createPersonRow(Persoana p) {
        if (p != null && !modelPersoana.contains(p)) { // Exclude duplicatele
            modelPersoana.add(p);
        }
    }
    private void populatePersonList(){
        modelPersoana.clear();
        Pageable pageable=new Pageable(currentPage,PAGE_SIZE);
        Page<Persoana> lista_persoane=service.getPagedPersoaneForSoferID(sofer.getId(),pageable);
        for(Persoana p:lista_persoane.getElementsOnPage()){
            createPersonRow(p);
        }
        Integer totalNumberOfPages = (int)(Math.ceil((double)lista_persoane.getTotalNumberElements() / PAGE_SIZE));
        label_page.setText("Page "+ currentPage + "/" + totalNumberOfPages);
        if(currentPage == 1)
            prev.setDisable(true);
        else
            prev.setDisable(false);
        if(currentPage == totalNumberOfPages)
            next.setDisable(true);
        else
            next.setDisable(false);
    }

    public void handle_date(ActionEvent actionEvent) {
        Iterable<Comanda> comenzi=service.getComenziData(date_picker.getValue(),sofer.getId());
        modelComenzi.setAll((Collection<? extends Comanda>) comenzi);
    }
}
