<?php
// Exécuter un session_start() pour avoir accès à la variable $_SESSION dans tous les cas
session_start();

/*

 Ce code permet l'affichage et le fonctionnement de la page CRUD de l'administrateur,
 alors tout naturellement on commence par vérifier qu'il y a bien un usager actif,
 et qu'il s'agit bien d'un administrateur

 */

// S'il n'y a pas d'utilisateur actif (compte connecté)
if (!isset($_SESSION["userRole"])) {

    // Il est redirigé vers la page de logging
    header("location:../Auth/login.php ");

// Et s'il y en a un
} else {

    // Vérifier qu'il s'agisse d'un administrateur
    if ($_SESSION["userRole"] != "Admin") {

        // S'il ne l'est pas, il est redirigé vers la page d'accueil client connecté
        header("location:../Client/logged_client.php ");
    }
}

/* Après ces vérifications, nous sommes assurés que nous avons un administrateur connecté.
   Alors, il faut lui afficher la page avec les outils appropriés.
*/

// Nous récupérons nos outils (classes et méthodes ..)
require("../../tbs_class.php");
require_once '../../Controllers/ProductController.php';
require_once '../../Models/product.php';

/*

Dans cette page l'administrateur a un formulaire d'ajout de produit affiché au milieu de la page, lui donnant la possibilité
de définir une nouvelle ligne dans la base de données, correspondant a à nouveau produit. Pour lui permettre de réaliser
cette opération :

*/

// On instancie un objet de la classe ProductController
$productController = new ProductController;

// On récupère la liste des catégories, pour les proposer dans une liste d'options lors de la définition du nouveau produit
$categories = $productController->getCategories();

// On déclare un message d'erreur vide que l'on va adapter en fonction du déroulement des opérations
$errMsg = "";


// Vérifier que les valeurs transmises par le "post" sont bien renseignées
if (isset($_POST['name']) && isset($_POST['description']) && isset($_POST['price']) && isset($_POST['quantity']) && isset($_FILES["image"])) {


    if (!empty($_POST['name']) && !empty($_POST['description']) && !empty($_POST['price']) && !empty($_POST['quantity'])) {


        // A ce stade nous disposons d'un ensemble de valeurs que l'on doit affecter aux attributs d'un nouvel objet produit

        // Commencer par instancier un nouvel objet de la classe Product
        $product = new Product;

        // Et affecter les valeurs transmises par le post aux attributs de ce nouvel objet
        $product->name = $_POST['name'];
        $product->description = $_POST['description'];
        $product->price = $_POST['price'];
        $product->quantity = $_POST['quantity'];
        $product->categoryid = $_POST['category'];

        /*
        Pour l'attribut image:
        Nous avons vu lors de la construction de la base de données, que l'attribut image est un "chemin d'accès" (bonnes pratiques).
        Dans le formulaire d'ajout de nouveau produit, l'administrateur récupère un fichier image d'un repertoire quelconque, il faut pouvoir :
        - stocker le contenu de l'image spécifiée, dans le repertoire qu'on a choisi pour les images de nos produits.
        - construire le chemin d'accès à cette image stockée, pour le fournir en valeur pour l'attribut image dans la bdd

        Les pas suivants permettent de réaliser cette opération :

        */

        // Concaténer l'adresse du repertoire d'images produits, choisi pour l'application, avec le nom du fichier récupéré,
        // le résultat est une chaine de caractères représentant le chemin d'accès à cette image dans notre application
        $location = "../../Views/assets/img/produits/". $_FILES["image"]["name"];

        // Placer le contenu de l'image dans cette nouvelle adresse, si l'opération est réussie :
        if (move_uploaded_file($_FILES["image"]["tmp_name"], $location)) {

            // on affecte cette valeur (adresse) à l'attribut image de notre objet $product
            $product->image = $location;
            /*
             On fait appel à la méthode addProduct de la classe productController, et on l'alimente avec
             le paramètre $product, Si l'opération est réussie (création d'une nouvelle ligne d'un nouveau produit,
             dans la table "produits" de la base de données :
            */
            if ($productController->addProduct($product)) {

                // On redirige vers la vue crud.php, ou l'administrateur pourra constater une nouvelle ligne produit dans l'affichage
                header("location: crud.php");

            // si la methode addProduct() rencontre un problème:
            } else {

                // On adapte le message d'erreur
                $errMsg = "L'ajout n'a pas pu aboutir, merci de réessayer";
            }

        // Si le contenu de l'image téléchargée n'a pas pu être stockée à l'adresse spécifiée
        } else {

            // On adapte le message d'erreur
            $errMsg = "Erreur lors du chargement";
        }

    // Si l'un des champs du formulaire n'a pas été correctement rempli, adapter le message d'erreur en conséquence
    } else {
        $errMsg = "Merci de remplir tous les champs";
    }
}


// Pour le message d'accueil et le statut, on récupère les valeurs pour l'administrateur connecté
$utilisateur = $_SESSION["userName"];
$role = $_SESSION["userRole"];


// on utilise tbs pour afficher (commentaires plus détaillés dans la vue d'accueil par exemple)
$tbs = new clsTinyButStrong ;
$tbs->LoadTemplate("Views/Admin/crud2.html");

// Options de la catégorie, dans le menu select déroulant, l'administrateur a juste à choisir le nom de la catégorie dans la liste, et
// ça sera l'id de la catégorie qui sera transmis dans le formulaire.
$tbs->MergeBlock('categorie', $categories);


$tbs->MergeField('errMsg', $errMsg);
$tbs->MergeField('utilisateur', $utilisateur);
$tbs->MergeField('role', $role);
$tbs->Show();

