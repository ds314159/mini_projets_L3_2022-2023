<?php 
/*
  Dans ce qui suit, nous construisons une classe pour controler les processus d'authentification.
  C'est une classe ayant pour attribut un objet de la classe DBController, et qui sera
  dotée de deux méthodes :
 -login()
 -register()

 Le but est d'avoir un outil compact et fiable, nous permettant facilement de réaliser les opérations de logging et
 d'enregisterement
  */



// Récupérer les outils déjà construits
require_once '../../Models/user.php' ;
require_once '../../Controllers/DBController.php' ;


class AuthController
{

    protected $db;

    /*
     Methode login(), prend un objet User en paramètre, retourne un boolean.
     Permet de vérifier l'existance d'un utilisateur dans la base de données
     */
    public function login(User $user)
    {
        // on affecte à l'attribut $db d'un objet de cette classe, la valeur "un objet de la classe DBController" fraichement instancié
        $this->db=new DBController;

        // on fait appel à la méthode openConnection() de $db pour établir une connexion avec la bdd
        if($this->db->openConnection())
        {
            /*
            Si la connexion est établie, on construit une requête SQL avec les valeurs des attributs email et password
            du paramètre, requête pour récupérer dans la base de données tous les attributs de l'utilisateur qui aura l'email
            et le password de l'objet $user

            */
            $query="select * from users where email='$user->email' and password ='$user->password'";

            // On execute cette requête en faisant appel à la méthode select() de l'objet $db, et on récupère le résultat
            $result=$this->db->select($query);

            // Plusieurs cas de figures possibles:

            // Si l'execution de la requête retourne false
            if($result===false)
            {
                // On affiche un message d'erreur dans la console
                echo "Erreur de requête !";

                // et la fonction s'arrête en retournant false
                return false;
            }

            // si le résultat est différent de false, la requête s'est bel et bien exécutée, étudions la réponse de la bdd
            else
            {
                // Aucune ligne dans la table users de la bdd, ne contient l'usager spécifié en paramètre
                if(count($result)==0)
                {
                    session_start();

                    // on stoque dans la variable $_SESSION un message d'erreur en conséquence
                    $_SESSION["errMsg"]="Identifiant ou mot de passe erronnés !";

                    // on ferme la connexion
                    $this->db->closeConnection();

                    // et la fonction s'arrête en retournant false
                    return false;
                }

                // S'il y a bien un usager repertoriée dans la bdd avec le mail et le password du paramètre $user
                else
                {
                    session_start();

                    // ayant récupéré tous les attributs de cet usager, j'affecte son id et son nom à la session
                    $_SESSION["userId"]=$result[0]["id"];
                    $_SESSION["userName"]=$result[0]["name"];


                    // Pour le rôle, qui a été récupéré sous forme d'un chiffre, je l'affecte à la session sous forme de "Client" ou "Admin"
                    // cela permet de faciliter l'affichage du statut de l'usager dans la vue (ne pas avoir à chaque fois à convertir)
                    if($result[0]["roleid"] == 2 )
                    {
                        $_SESSION["userRole"]="Client";
                    }
                    else
                    {
                        $_SESSION["userRole"]="Admin";
                    }

                    // Systématiquement fermer la connexion à la fin du besoin
                    $this->db->closeConnection();

                    // et la fonction login() s'arrête en retournant true
                    return true;
                }
            }
        }

        // Si openConnection() rencontre un problème lors de son execution
        else
        {
            // on affiche un message d'erreur dans la console
            echo "Erreur de connexion à la base de données !";

            // et la fonction s'arrête en retournant false
            return false;
        }
    }

    /*
     Methode register(), prend un objet User en paramètre, retourne un boolean.
     Permet d'enregistrer un nouvel utilisateur dans la base de données
     */

    // Les commentaires seront plus brefs vu les similarités avec login() !
    public function register(User $user)
    {
        $this->db=new DBController;

        // Si la connexion avec la bdd est établie
        if($this->db->openConnection())
        {
            // on construit une requête d'insertion avec les attributs de l'objet $user
            $query="insert into users values ('','$user->name','$user->email','$user->password',2)";

            // on exécute cette requête grâce à la méthode insert(), et on récupère le résultat
            $result=$this->db->insert($query);

            /*
             Si l'insertion est bel et bien executée, l'usager est désormais repertorié dans la bdd, dispose d'un compte client
            et passe en mode connecté, une session est ouverte aux caractéristiques de l'usager.
            Notons que l'enregistrement est par defaut uniquement pour les clients, nous pouvons imaginer
            que les administrateurs soient créés directement dans la bdd par un super Admin.
            La connexion est ensuite fermée et la fonction s'arrête en retournant true.
             */
            if($result!=false)
            {
                session_start();
                $_SESSION["userId"]=$result;
                $_SESSION["userName"]=$user->name;
                $_SESSION["userRole"]="Client";
                $this->db->closeConnection();
                return true;
            }
            /*
             Si l'insertion n'a pas pu s'exécuter correctement, on fait remonter l'erreur dans la variable $_SESSION,
             on ferme la connexion et la fonction s'arrête en retournant false
            */
            else
            {

                $_SESSION["errMsg"]="Une erreur est survenue.. réessayer plus tard !";
                $this->db->closeConnection();
                return false;
            }
        }

        /*
         Si la connexion n'a pas pu s'établir, on affiche un message dans la console et la fonction s'arrête en retournant false.
         */
        else
        {
            echo "Erreur de connexion à la base de données !";
            return false;
        }
    }
    
}

?>


