<?php
// récupérer nos outils encapsulés
require("../../tbs_class.php");
require_once '../../Controllers/ProductController.php';
require_once '../../Models/product.php';
// executer un session_start() afin d'avoir accès aux variables de la session
session_start();


/* Nous gérons ici sur la page d'accueil du site, qui doit s'afficher en dehors d'un client ou un administrateur loggé,
   ou si on y est redirigé suite à une demande de déconnexion. */


/*nous commençons par vérifier qu'il s'agit pas d'une redirection suite demande de deconnexion, si c'est le cas, on
   détruit la session (effacer les valeurs de variables de l'usager en cour) */

if(isset($_GET["logout"]))
{
    session_start();
    session_destroy();
}


// S'il n'y a pas eu redirection suite à une demande de logout, on vérifie si un usager est loggé :
if (isset($_SESSION["userRole"])) {

    // Si l'usager est un client, on le dirige vers la page d'accueil client loggé
    if($_SESSION["userRole"]=="Client"){
        header("location:../../Views/Client/logged_client.php ");
    }

    // Si l'usager est un admin, on le dirige vers la page d'administration
    if($_SESSION["userRole"]=="Admin"){
        header("location:../../Views/Admin/crud.php ");
    }

}

// Si aucun usager n'est loggé, on affiche notre page d'accueil, pour celà:

// Il faut récupérer de la base de données la liste des produits et leurs caractéristiques, ainsi que la liste des catégories:
$productController = new ProductController;
$categories = $productController->getCategories();
$produits = $productController->getAllProductsWithImages();


// tbs est la pour charger le gabarit et y injecter les données récupérées de la base de données:

// Instancier un objet tbs
$tbs = new clsTinyButStrong ;

// Charger le template html
$tbs->LoadTemplate("Views/Client/home.html");

// Injecter toutes les catégories dans la vue ( onglet catégories, en haut à gauche )
$tbs->MergeBlock('categorie', $categories);

// Injecter tous les produits disponibles dans la vue ( espace contenu, au centre )
$tbs->MergeBlock('produit', $produits);

// Et... afficher le résultat, magique tbs !
$tbs->Show();

