<?php

/* Nous construisons ici le modèle d'un objet utilisateur, il sera caractérisé par cinq attributs, son id, son nom,
   son email, son mot de passe, et le rôle qu'il joue ( dans notre cas : client normal ou administrateur).
   le constructeur par defaut n'est pas modifié car il fait le boulot par rapport à notre besoin.

 */

class User
{
    public $id;
    public $name;
    public $email;
    public $password;
    public $roleid;


}

?>