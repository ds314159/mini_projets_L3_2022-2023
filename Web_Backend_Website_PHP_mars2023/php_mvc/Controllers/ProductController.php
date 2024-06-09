<?php
/*
  Dans ce qui suit, nous construisons une classe pour controler les processus d'authentification.
  C'est une classe ayant pour attribut un objet de la classe DBController, et qui sera
  dotée de 6 méthodes qui interrogent la base de données et récupèrent la réponse.

 - getCategories() : pour avoir la liste des catégories existantes dans la bdd
 - getAllProducts() : pour avoir la liste des produits existants dans la base de données, sans l'attribut image
 - getAllProductsWithImages() : pour avoir la liste des produits existants dans la base de données, avec le chemin d'accès à l'image
 - getCategoryProducts() : pour avoir tous les produits d'une categorie dont l'id est rentré en paramètre
 - addProduct() : pour ajouter une ligne produit dans le tableau produits de la base de données
 - deleteProduct() : Pour supprimer une ligne produit dans le tableau produits de la bdd


 Le but est d'avoir un outil compact et fiable, nous permettant facilement de réaliser des opérations de lecture et d'insertion
 dans la base de données.
  */

// Commençons par récupérer nous outils
require_once '../../Models/product.php' ;
require_once '../../Controllers/DBController.php';

class ProductController
{
    protected $db;

    /*
    Methode getCategories(), ne prend pas de paramètre, retourne false ou l'array des lignes de catégories obtenues
    suite à l'interrogation de la bdd
     */
    public function getCategories()
    {
        // instancier un nouvel objet DBController et l'affecter à l'attribut $db
         $this->db=new DBController;

         // faire appel à openConnection()
         if($this->db->openConnection())
         {
             // Si la connexion est établie

             // Selectionner toutes les lignes du tableau categories de la bdd et les retourner en résultat
            $query="select * from categories";
            return $this->db->select($query);
         }

         // Si un problème de connexion survient
         else
         {
             // le signaler dans la console et retourner false
            echo "Error in Database Connection";
            return false; 
         }
    }

    /*
     Notons pour la suite, pour éviter les redondances de commentaires,
    toutes ces petites méthodes fonctionnent sur le même principe:
    - établir une connexion avec la bdd
    - exécuter une requête sql
    - retourner le résultat, et le message approprié

    L'utilisation des méthodes de la classe DBController, est plus détaillée dans les commentaires de la classe AuthController
     */

    /*
    Methode addProduct(), permet d'insérer une nouvelle ligne dans le tableau produit de la bdd.
    Prend en paramètre un objet Produit, retourne false ou l'id du dernier produit inséré.
     */
    public function addProduct(Product $product)
    {
         $this->db=new DBController;
         if($this->db->openConnection())
         {
            $query="insert into products values ('','$product->name','$product->description','$product->price','$product->quantity','$product->image',$product->categoryid)";
            return $this->db->insert($query);
         }
         else
         {
            echo "Error in Database Connection";
            return false; 
         }
    }

    /*
    Methode getAllProducts(), ne prend pas de paramètre, retourne false ou l'array des lignes de la table produits de la base de données, sans l'attribut image.
    suite à l'interrogation de la bdd
     */
    public function getAllProducts()
    {
         $this->db=new DBController;
         if($this->db->openConnection())
         {
            $query = "SELECT products.id, products.name, products.price, products.quantity, categories.name AS `category` FROM products, categories WHERE products.categoryid = categories.id";

            return $this->db->select($query);
         }
         else
         {
            echo "Error in Database Connection";
            return false; 
         }
    }

    /*
    Methode deleteProduct(), permet de supprimer une ligne de la table produits de la bdd.
    Prend en paramètre l'id du produit à supprimer, retourne un boolean.
     */
    public function deleteProduct( $id)
    {
         $this->db=new DBController;
         if($this->db->openConnection())
         {
            $query="delete from products where id = $id";
            return $this->db->delete($query);
         }
         else
         {
            echo "Error in Database Connection";
            return false; 
         }
    }
        /*
        Methode getAllProductsWithImages(), ne prend pas de paramètre, retourne false ou l'array des lignes de la table produits de la base de données, avec l'attribut image.
        suite à l'interrogation de la bdd
         */
    public function getAllProductsWithImages()
    {
         $this->db=new DBController;
         if($this->db->openConnection())
         {
            $query="select products.id,products.name,products.price,products.quantity,categories.name as 'category',products.image, products.description from products,categories where products.categoryid=categories.id;";
            return $this->db->select($query);
         }
         else
         {
            echo "Error in Database Connection";
            return false; 
         }
    }

        /*
        Methode getCategoryProducts(), prend en paramètre l'id de la catégorie ciblée, retourne false ou l'array des lignes de la table catégorie de la base de données, qui ont pour categorieid le paramètre $id.
        suite à l'interrogation de la bdd
         */
    public function getCategoryProducts($id)
    {
         $this->db=new DBController;
         if($this->db->openConnection())
         {
            $query="select products.id,products.name,price,quantity,categories.name as 'category',image from products,categories where products.categoryid=categories.id and categories.id=$id;";
            return $this->db->select($query);
         }
         else
         {
            echo "Error in Database Connection";
            return false; 
         }
    }
    
    
}

