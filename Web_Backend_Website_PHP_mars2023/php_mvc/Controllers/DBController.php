<?php

/*
  Dans ce qui suit, nous construisons une classe pour gérer les connexions et les requêtes faites à la bdd.
  C'est une classe ayant pour attribut un objet de la classe DBController, et qui sera
  dotée de deux méthodes :
 - openConnection(): pour ouvrir une connexion avec la bdd
 - closeConnection() : pour fermer la connexion avec la bdd
 - select(), insert(), delete() pour exécuter des requêtes avec la bdd

 Le but est d'avoir un outil compact et fiable, nous permettant facilement de dialoguer avec la bdd

 Le choix est fait d'utiliser l'extension mySQLi (mySQL improved) comme interface d'accès à la bdd
  */


class DBController
{
    // identifiants et password
    public $dbHost="mysql02.univ-lyon2.fr";
    public $dbUser="php_memansour";
    public $dbPassword="HT_nNV6QW/8Xvky/L633pt2lp";
    public $dbName="php_memansour";

    // attribut d'instance
    public $connection;

    /*
     Methode openConnection(), ne prend pas de paramètre, retourne un boolean.
     Permet d'ouvrir une connexion avec la bdd
     */
    public function openConnection()

    {
        // établir la connexion avec une nouvelle instance de mysqli, et les paramètres de la bdd
        $this->connection=new mysqli($this->dbHost,$this->dbUser,$this->dbPassword,$this->dbName);

        // si un problème de connexion est survenu
        if($this->connection->connect_error)
        {
            // afficher un message dans la console et retourner false
            echo " Erreur de connexion : ".$this->connection->connect_error;
            return false;
        }
        else
        {
            // sinon la connexion est établie, la fonction s'arrête en retournant true
            return true;
        }

    }

    /*
     Methode closeConnection(), ne prend pas de paramètre, ne retourne pas de valeur.
     Permet de fermer une connexion avec la bdd
     */
    public function closeConnection()
    {
        if($this->connection)
        {
            // Si une connexion est en coursn elle est fermée par la méthode close de la classe mysqli
            $this->connection->close();
        }
        else
        {
            // s'il n'y a pas de connexion, on affiche un message dans la console
            echo "Pas de connexion à fermer !";
        }
    }


    /*
     Methode select(), prend en paramètre une chaine de caractères qui represente une requête en langage SQL,
     retourne false ou les lignes récupérées de la bdd. elle est utilisée quand une connexion est déjà établie avec la bdd
     */
    public function select($qry)
    {
        // On soumet la requête avec la methode query() de mysqli
        $result=$this->connection->query($qry);

        // Si pas de résultat
        if(!$result)
        {
            // on récupère l'erreur grâce à la méthode mysqli_error, et on l'affiche dans la console, la fonction s'arrête en retournant false
            echo "Erreur : ".mysqli_error($this->connection);
            return false;
        }

        // S'il y a bien un résultat, on les récupère grâce à la méthode fetch_all appliqué au résultat $resultat, la fonction s'arrête en retournant les lignes récupérées
        else
        {
             return $result->fetch_all(MYSQLI_ASSOC);
        }

    }

    /*
     Methode insert(), prend en paramètre une chaine de caractères qui représente une requête d'insertion en langage SQL,
     retourne false ou l'id de la dernière insertion. Elle est utilisée quand une connexion est déjà établie avec la bdd
     */
    public function insert($qry)
    {
        $result=$this->connection->query($qry);
        if(!$result)
        {
            echo "Erreur : ".mysqli_error($this->connection);
            return false;
        }
        else
        {
             return $this->connection->insert_id;
        }

    }

    /*
     Methode delete(), prend en paramètre une chaine de caractères qui représente une requête de suppression en langage SQL,
     retourne un boolean. Elle est utilisée quand une connexion est déjà établie avec la bdd.
     */
    public function delete($qry)
    {
        $result=$this->connection->query($qry);
        if(!$result)
        {
            echo "Erreur : ".mysqli_error($this->connection);
            return false;
        }
        else
        {
             return $result;
        }

    }

}

