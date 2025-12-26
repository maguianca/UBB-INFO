package com.example.taximetrie2.controller;

import com.example.taximetrie2.domeniu.*;
import com.example.taximetrie2.events.UtilizatorEntityChangeEvent;
import com.example.taximetrie2.observer.Observer;
import com.example.taximetrie2.paging.Page;
import com.example.taximetrie2.paging.Pageable;
import com.example.taximetrie2.service.Service;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.util.Collection;

public class SoferController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Stage dialogStage;
    private Sofer sofer;
    @FXML
    private TableView<Cerere> tabel1;
    @FXML
    private TableColumn<Cerere,String> nume;
    @FXML
    private TableColumn<Cerere,String>locatie;
    @FXML
    private TableColumn<Cerere,Integer>client;
    @FXML
    private TextField minute;
    @FXML
    private TableView<Persoana>tableclienti;
    @FXML
    private TableColumn<Persoana,String>username;
    @FXML
    private TableColumn<Persoana,String>numeclient;
    @FXML
    private Label label_page;
    Integer currentPage = 1;
    private static final Integer PAGE_SIZE = 2;
    @FXML
    private Button prev;
    @FXML
    private Button next;
    private ObservableList<Cerere> model1 = FXCollections.observableArrayList();
    private ObservableList<Persoana> modelc = FXCollections.observableArrayList();
    private ObservableList<Comanda> modelComenzi = FXCollections.observableArrayList();
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


    public void setService(Service service, Stage dialogStage, Sofer sofer) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.sofer = sofer;
        initmodel();
        this.service.addObserver(this);
        populatePersonList();

    }
    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initmodel();
    }
    @FXML
    public void initialize(){
        nume.setCellValueFactory(cellData -> {
            Long idclient = cellData.getValue().getId_client();
            Persoana persoana = service.getPersoanaId(idclient);
            return new ReadOnlyObjectWrapper<>(persoana.getNume());
        });
        locatie.setCellValueFactory(new PropertyValueFactory<>("adresa"));
        tabel1.setItems(model1);
        client.setCellValueFactory(new PropertyValueFactory<>("id_client"));
        tabel1.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        tabel1.setItems(model1);
        tableclienti.setItems(modelc);
        username.setCellValueFactory(new PropertyValueFactory<>("username"));
        numeclient.setCellValueFactory(new PropertyValueFactory<>("nume"));
        tabel_comenzi.setItems(modelComenzi);
        nume_client.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getPersoana().getNume()));
    }
    public void initmodel(){
        model1.setAll(service.getAllCerere());
        populatePersonList();
        media.setText(service.media_comenzi(LocalDate.now(),sofer.getId()).toString());
        nume_client_fidel.setText(service.client_fidel(sofer.getId()));
    }

    public void handleonoreaza(ActionEvent actionEvent) {
        Cerere cerereSelectata = tabel1.getSelectionModel().getSelectedItem();
        if (cerereSelectata == null) {
            showErrorMessage("Te rog să selectezi o cerere din tabel.");
            return;
        }
        String minuteText = minute.getText();
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

            service.save_oferta(new Oferta(cerereSelectata.getId_client(),sofer.getId(),cerereSelectata.getId(), minute));
            showConfirmationMessage("Oferta a fost trimisa!");
            initmodel();

        } catch (NumberFormatException e) {
            showErrorMessage("Numărul de minute trebuie să fie un număr valid.");
        }
    }
    private void showConfirmationMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Confirmare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
    private void showErrorMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Eroare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    public void handlenext(ActionEvent actionEvent) {
        currentPage++;
        populatePersonList();
    }

    public void handleprev(ActionEvent actionEvent) {
        currentPage--;
        populatePersonList();
    }
    private void populatePersonList(){
        modelc.clear();
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
    private void createPersonRow(Persoana p) {
        if (p != null && !modelc.contains(p)) { // Exclude duplicatele
            modelc.add(p);
        }
    }
    public void handle_date(ActionEvent actionEvent) {
        Iterable<Comanda> comenzi=service.getComenziData(date_picker.getValue(),sofer.getId());
        modelComenzi.setAll((Collection<? extends Comanda>) comenzi);
    }

}
