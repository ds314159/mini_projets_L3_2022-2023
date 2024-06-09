<?php

// récupérer nos outils encapsulés
require("../../tbs_class.php");
require_once '../../Controllers/ProductController.php';
require_once '../../Models/product.php';

// executer la commande session_start() afin d'avoir accès aux variables de la session
session_start();


// Nous gérons ici sur la page d'un client loggé:

// nous commençons par vérifier qu'il y a bien un usager loggé ( notons que l'admin a accès à cette page même s'il n'est pas client)

// si l'usager n'est pas loggé :
if (!isset($_SESSION["userRole"])) {

    // On le dirige vers la page d'accueil standard

    header("location:../../Views/Client/home.php ");


}

// Si l'usager est loggé, on affiche la page complétée par:

// 1-Les données sur les produits
$productController = new ProductController;
$categories = $productController->getCategories();
$produits = $productController->getAllProductsWithImages();

//2-Les données sur le client
$utilisateur = $_SESSION["userName"];
$role = $_SESSION["userRole"];

// tbs est la pour charger le gabarit et y injecter les données récupérées de la base de données:

// Instancier un objet tbs
$tbs = new clsTinyButStrong ;

// Charger le template html
$tbs->LoadTemplate("Views/Client/logged_client.html");

// Injecter toutes les catégories dans la vue ( onglet catégories en haut à gauche )
$tbs->MergeBlock('categorie', $categories);

// Injecter tous les produits disponibles dans la vue ( espece contenu au centre )
$tbs->MergeBlock('produit', $produits);

// Injecter le nom de l utilisateur dans le message de bienvenue ( visible après appui sur l'icone image utilisateur en haut à droite )
$tbs->MergeField('utilisateur', $utilisateur);

// Injecter le role de l'utilisateur dans le message de "statut de l'utilisateur" ( idem )
$tbs->MergeField('role', $role);

// Et... afficher le résultat, magique tbs !
$tbs->Show();
