package application;

import javaa_native.JNI;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.stage.Stage;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.layout.StackPane;


public class Main extends Application {
	boolean poc = false;
	boolean click = false;
	boolean first = true;
	
	//novo
	//boolean pisi = false;
	//boolean brisi = false;
	
	JNI jn = new JNI();
	String s2 = "C:/Users/PC/Desktop/baza.txt"; // putanja do txt fajla
	String s3 = "C:/Users/PC/Desktop/baza.db"; // putanja do db fajla
	 @Override
	    public void start(Stage stage) {
		 
	        CheckBox checkBox = new CheckBox("Ucitaj staru");

	        checkBox.setOnAction(e -> {
	            if (checkBox.isSelected()) {
	            	click = true;
	            } else {
	            	click = false;
	            }
	            checkBox.setDisable(true);
	        });
		 
	        TextField textField = new TextField();
	        textField.setPromptText("Unesi komandu");

	        Button commandButton = new Button("Klikni");
	        Button saveButton = new Button("Save");
	        
	        saveButton.setOnAction(e -> {
	        	jn.dajKomandu("SAVE SQL", 'd', s2, s3);
	        });
	        
	        //novo
	        TextField selectedTab = new TextField();
	        selectedTab.setPromptText("Unesi tabelu");
	        CheckBox select = new CheckBox("Pisi");
	        CheckBox dellete = new CheckBox("Brisi");
	        
	        select.setOnAction(e -> {
	            if (select.isSelected()) {
	            	dellete.setSelected(false);
	            }
	        });

	        dellete.setOnAction(e -> {
	            if (dellete.isSelected()) {
	            	select.setSelected(false);
	            }
	        });
	        
	        commandButton.setOnAction(e -> {
	        	char dn = 'd';
	        	if(poc) {
		        	if(checkBox.isSelected() && first) {
		        		dn = 'd';
		        		first = false;
		        	}
		        	else if(!checkBox.isSelected()) {
		        		dn = 'n';
		        		first = false;
		        	}
	        	}
	        	String enteredText = jn.dajKomandu(textField.getText(), dn, s2, s3);
	            Label Label = new Label(enteredText);
	            String tables = "Trenutne tabele\n" + jn.citajTabele(s2, s3);
	            Label Label2 = new Label(tables);

	            VBox leftVBox = new VBox(10); // razmak izmedju el
	            leftVBox.setPadding(new Insets(20)); // sirina granice oko boxa
	            leftVBox.getChildren().addAll(checkBox, saveButton, Label2);
	            
	            VBox rightVBox = new VBox(10);
	            rightVBox.setPadding(new Insets(20));
	            rightVBox.getChildren().addAll(textField, commandButton, Label);

	            //novo
	            String res;
	            Label Label3;
	            if(select.isSelected()) {
	            	res = "SELECT * FROM ";
	            	res += selectedTab.getText();
	            	Label3 = new Label(jn.dajKomandu(res, 'd', s2, s3));
	            }
	            else if(dellete.isSelected()) {
	            	res = "DROP TABLE ";
	            	res += selectedTab.getText();
	            	Label3 = new Label(jn.dajKomandu(res, 'd', s2, s3));
	            }
	            else {
	            	res = "Ispis tabele";
	            	Label3 = new Label();
	            }
	             
	            VBox centerVBox = new VBox(10);
	            centerVBox.setPadding(new Insets(20));
	            centerVBox.getChildren().addAll(selectedTab, select, dellete, Label3);
	            
	            BorderPane borderpane = new BorderPane();
	            borderpane.setLeft(leftVBox); // levu ubacujemo u levu sekciju
	            borderpane.setRight(rightVBox);
	            borderpane.setCenter(centerVBox);
	            
	            //kreiramo scenu zadate sirine i visine
	            Scene scene = new Scene(borderpane, 600, 500);

	            //postavljanje primarne scene
	            stage.setScene(scene);
	            stage.setTitle("SQL3");
	            stage.show();
	            poc = true;
	        });
	        
	        VBox vbox = new VBox(10);
	        vbox.setPadding(new Insets(20));
	        vbox.getChildren().addAll(textField, commandButton);

	        Scene scene = new Scene(vbox, 600, 500);

	        //najnovije
	        
	        stage.setOnCloseRequest(event -> {
	            event.consume();
	            
	            // prikaz prozora
	            Alert conf = new Alert(AlertType.CONFIRMATION);
	            conf.setTitle("Saving");
	            conf.setHeaderText("Da li zelite da sacuvate bazu?");
	            conf.setContentText("Kliknite YES da se sacuva u SQL");

	            // dodavanje dugmica
	            ButtonType buttonYes = new ButtonType("YES");
	            ButtonType buttonNo = new ButtonType("NO");
	            conf.getButtonTypes().setAll(buttonYes, buttonNo);

	            // osluskivac za dugmice
	            conf.showAndWait().ifPresent(response -> {
	                if (response == buttonYes) {
	                	jn.dajKomandu("SAVE SQL", 'd', s2, s3); //cuvanje u bazu
	                	stage.close(); // izlazi iz prozora
	                    Platform.exit(); // izlaz iz aplikacije
	                }
	                else {
	                	stage.close();
	                    Platform.exit();
	                }
	            });
	        });
	        
	        //////////
	        
	        
	        stage.setScene(scene);
	        stage.setTitle("SQL");
	        stage.show();
	        commandButton.fire();
	    }
	
	
	public static void main(String[] args) {
		launch(args);
	}
}
