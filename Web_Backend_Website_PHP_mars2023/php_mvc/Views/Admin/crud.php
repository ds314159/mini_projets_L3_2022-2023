<?php

// Exécuter un session_start() pour avoir accès à la variable $_SESSION dans tous les cas
session_start();

 /*

 Ce code permet l'affichage et le fonctionnement de la page CRUD de l'administrateur,
 alors tout naturellement on commence par vérifier qu'il y a bien un usager actif,
 et qu'il s'agit bien d'un administrateur

 */

// S'il n'y a pas d'utilisateur actif ( compte connecté)
if (!isset($_SESSION["userRole"])) {

    // il est redirigé vers la page de logging
    header("location:../Auth/login.php ");

//  Et s'il y en a un,
} else {

    // on vérifie que c'est bel et bien un administrateur
    if ($_SESSION["userRole"] != "Admin") {

        // S'il ne l'est pas, on le redirige vers la page d'accueil des clients connectés
        header("location:../Client/logged_client.php ");
    }
}


/* Après ces vérifications, nous sommes assurés que nous avons un administrateur connecté.
   Alors, il faut lui afficher la page avec les outils appropriés.
*/

// Nous récupérons nos outils ( classes et méthodes ..)
require("../../tbs_class.php");
require_once '../../Controllers/ProductController.php';
require_once '../../Models/product.php';

/*
Dans cette page l'administrateur a la liste complète des produits affichée au milieu, avec un bouton lui permettant
d'éliminer un produit à la fois ( effacer la ligne correspondante au produit choisi de la base de données).
*/

// On instancie un objet de la classe ProductController
$productController = new ProductController;

// On récupère la liste des produits diponibles en utilisant le Getter des produits de l'objet $productController
$produits = $productController->getAllProducts();

// On déclare un message un vide que l'on va adapter en fonction du déroulement de nos opérations
$deleteMsg = "";

// S'il y a réception d'une requête de suppression du formulaire
if (isset($_POST["delete"])) {

    // et si cette requête n'est pas vide
    if (!empty($_POST["productId"])) {

        // la méthode deleteProducte() offerte par le controleur de produit permet d'effacer la ligne du produit dont l'id a été
        // posté par le formulaire,de la base de données.
        if ($productController->deleteProduct($_POST["productId"])) {

            // Si la méthode deleteProduct() est executée avec succès:
            // On affecte une valeur de succès de l'opération au message à afficher
            $deleteMsg = "Produit supprimé";

            // On re-récupère la liste des produits, pour que le produit supprimé ne soit plus affiché
            $produits = $productController->getAllProducts();
        }
    }
}


// on récupère le nom et le rôle de l'utilisateur
$utilisateur = $_SESSION["userName"];
$role = $_SESSION["userRole"];


// On affiche le tout grâce à tbs:
$tbs = new clsTinyButStrong ;
$tbs->LoadTemplate("Views/Admin/crud.html");
$tbs->MergeBlock('produit', $produits);
$tbs->MergeField('deleteMsg', $deleteMsg);
$tbs->MergeField('utilisateur', $utilisateur);
$tbs->MergeField('role', $role);
$tbs->Show();





