<?php

// Récupérer nos outils
require("../../tbs_class.php");
require_once '../../Models/user.php';
require_once '../../Controllers/AuthController.php';

// Déclarer un message d'erreur vide qui sera affiné en fonction du déroulement
$errMsg="";

// Exécuter un session_start() s'il n'y a pas de session d'utilisateur actif en cours
if(!isset($_SESSION["userId"]))
{
  session_start();
}

// Vérifier si le formulaire a "posté" des éléments d'enregistrement d'un usager
if (isset($_POST['email']) && isset($_POST['password']) && isset($_POST['name'])) 
{
  // Si c'est le cas, vérifier que ces éléments sont bien renseignés (pas de champ de vide)
  if (!empty($_POST['email']) && !empty($_POST['password']) && !empty($_POST['name'])) 
  {
    // Si on a bien récupére un email, un password et un nom, on procède à la création d'un nouveau compte:

    // Instancier un objet de la classe User ( voir les commentaires associés à chaque classe et ses méthodes )
    $user=new User;

    // Instancier un objet de la classe AuthController ( voir les commentaires associés à chaque classe et ses méthodes )
    $auth=new AuthController;

    // Affecter les valeurs récupérées du post, aux attributs de l'objet user
    $user->name=$_POST['name'];
    $user->email=$_POST['email'];
    $user->password=$_POST['password'];

    /* exécuter la méthode register() de l'objet $auth, avec comme paramètre l'objet $user confectionné avec
       les valeurs récupérées du post.
       Si la méthode est executée avec succès, un nouvel utilisateur existe désormais dans la base de  données.
       On redirige en conséquence l'utilisateur vers la page de logging.
    */
    if($auth->register($user))
    {
      header("location: ../Auth/login.php");
    }
    /* Si la methode register() n'est pas exécutée avec succès, elle aura inscrit un message d'erreur dans la session,
       on affecte ce message d'erreur à la variable $errMsg à afficher dans la vue "register"
    */
    else
    {
      $errMsg=$_SESSION["errMsg"];
    }

  }
  // Si l'une des valeurs transmises par le post est vide, on adapte le message d'erreur pour l'afficher dans la vue "register"
  else
  {
    $errMsg="Merci de remplir tous les champs";
  }

}

// utiliser tbs pour récupérer et afficher le gabarit

//Instancier un objet tbs
$tbs = new clsTinyButStrong ;

// Charger le template html "register"
$tbs->LoadTemplate("Views/Auth/register.html");

// Injecter la variable $errMsg dans la vue
$tbs->MergeField('errMsg', $errMsg);

// Afficher le resultat
$tbs->Show();




