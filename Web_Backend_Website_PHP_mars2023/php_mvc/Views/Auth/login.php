<?php

// Boite à outils: récupérer nos outils encapsulés ( classes, methodes associées..)
require("../../tbs_class.php");
require_once '../../Models/user.php';
require_once '../../Controllers/AuthController.php';

// déclarer un message d'erreur vide, que l'on va affiner en fonction de l'execution de notre logique
$errMsg="";


// quand le formulaire est utilisé, on vérifie que les champs email et password de $_POST ont été initiés
if(isset($_POST['email']) && isset($_POST['password']))
{
    // dans ce cas , on vérifie qu'ils n'ont pas été initiés avec des champs vides
    if(!empty($_POST['email']) && !empty($_POST['password']) )
    {
        // Si les deux conditions précédentes sont remplies:
        // on sort la boite à outils, on instancie un objet de la classe User
        $user=new User;
        // ainsi qu'un objet AuthController
        $auth=new AuthController;
        // on affecte la valeur email postée, à l'attribut email de l'objet User
        $user->email=$_POST['email'];
        // on affecte la valeur password postée, à l'attribut password de l'objet User
        $user->password=$_POST['password'];
        // on utilise la méthode login() de l'objet Auth, avec cet $user en paramètre, et on vérifie le retour
        if(!$auth->login($user))
        {
            if(!isset($_SESSION["userId"]))
            {
                session_start();
            }

            // si la méthode login() renvoie false ( echec de la connexion), on récupère le message d'erreur
            // qu'elle a stockée dans $_SESSION et on l'affecte à notre variable message errMsg
            $errMsg=$_SESSION["errMsg"];
        }

        // Et si la méthode login() renvoie true, la connexion a eu lieu
        else
        {
            if(!isset($_SESSION["userId"]))
            {
                session_start();
            }

            // on redirige l'usager en fonction de son rôle:

            if($_SESSION["userRole"]=="Admin")
            {
                // s'il est "admin" on le dirige vers la page ou il peut créer lire mettre à jour et supprimer des données
                header("location: ../Admin/crud.php");
            }
            else
            {
                // si l'usager est juste un client, il est redirigé vers la page d'accueil des clients connectés
                header("location: ../Client/logged_client.php");
            }

        }

        
    }

    // si le champ email ou password n'a pas été rempli lors de l'envoi de la requête, un message adéquat est affecté
    else
    {
        $errMsg="Merci de remplir tous les champs";
    }
}


// utiliser tbs pour récupérer et afficher le gabarit:

// Instancier un objet de la classe tbs
$tbs = new clsTinyButStrong ;

// charger le template html
$tbs->LoadTemplate("Views/Auth/login.html");

// injecter le message d'erreur (s'il y en a un ), à partir de notre variable $errMsg
$tbs->MergeField('errMsg', $errMsg);

// afficher le résultat
$tbs->Show();




