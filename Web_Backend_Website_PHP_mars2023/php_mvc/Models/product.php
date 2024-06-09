<?php

/* Nous construisons ici le modèle d'un objet produit, il sera caractérisé par 7 attributs, l'id, le nom commercial,
   une description courte de 500 caractères, le prix, la quantité disponible en stock, l'image ( voir le commentaire associé),
   et l'id de la catégorie à laquelle il appartient.
   le constructeur par defaut n'est pas modifié car il fait le boulot par rapport à notre besoin.

 */

class Product
{
    public $id;
    public $name;
    public $description;
    public $price;
    public $quantity;
    /* Dans une première version, dans la bdd, l'image a été sockée sous forme binaire ( blob ), ceci s'est avéré
       contraire aux bonnes pratiques et source de bugs (en fonction de la nature de l'extension, problèmes de compatibilité
       avec le navigateur). Le correctif est : de stocker le chemin vers la photo. Ici le dossier des images de produits
       est stockée dans les assets/img/ . En conclusion, l'attribut $image est désormais une chaine de maximum 500 charactères
       spécifiant le chemin vers l'image du produit.
    */
    public $image;
    public $categoryid;

}

?>