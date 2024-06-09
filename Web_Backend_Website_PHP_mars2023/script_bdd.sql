-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Hôte : mysql02.univ-lyon2.fr
-- Généré le : mer. 12 juil. 2023 à 14:28
-- Version du serveur : 5.5.64-MariaDB
-- Version de PHP : 8.2.0alpha1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `php_memansour`
--

-- --------------------------------------------------------

--
-- Structure de la table `categories`
--

CREATE TABLE `categories` (
  `id` int(11) NOT NULL,
  `name` varchar(100) CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `categories`
--

INSERT INTO `categories` (`id`, `name`) VALUES
(1, 'Data Science'),
(2, 'Big Data'),
(3, 'Machine Learning'),
(4, 'Asimov');

-- --------------------------------------------------------

--
-- Structure de la table `products`
--

CREATE TABLE `products` (
  `id` int(11) NOT NULL,
  `name` varchar(220) CHARACTER SET utf8 NOT NULL,
  `description` varchar(499) CHARACTER SET utf8 NOT NULL,
  `price` varchar(10) CHARACTER SET utf8 NOT NULL,
  `quantity` int(11) NOT NULL,
  `image` varchar(500) CHARACTER SET utf8 NOT NULL,
  `categoryid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `products`
--

INSERT INTO `products` (`id`, `name`, `description`, `price`, `quantity`, `image`, `categoryid`) VALUES
(1, 'BI et Big data', 'L\'entreposage de données et l\'analyse en ligne (On-Line Analytical Processing _OLAP) se sont imposés comme des outils fondamentaux de l\'informatique décisionnelle (Business Intelligence - BI). Avec l\'avènement des mégadonnées (big data) caractérisées par leur très grand volume, leur vélocité et leur variété, et des technologies et infrastructures émergentes (NoSQL, Cloud, Hadoop...), ces outils d\'analyse et d\'aide à la décision sont confrontés à de nouveaux défis scientifiques.', '60.00', 22, '../../Views/assets/img/produits/BIetBigdata.webp', 2),
(2, 'Python pour la Data Science', 'Pour de nombreux chercheurs, Python constitue l\'outil de prédilection en raison de ses riches librairies de fonctions de traitement et d\'analyse de données. ', '39.95', 3, '../../Views/assets/img/produits/pythonpourladatascience.webp', 1),
(3, 'Big Data et Machine Learning', 'Cet ouvrage s\'adresse à tous ceux qui cherchent à tirer parti de  l\'énorme potentiel des « technologies Big Data », qu\'ils soient data  scientists, DSI, chefs de projets ou spécialistes métier. ', '24.99', 5, '../../Views/assets/img/produits/bigdataetmachinelearning.webp', 3),
(4, 'Fondation', 'En ce début de treizième millénaire, l\'Empire n\'a jamais été aussi puissant, aussi étendu à travers toute la galaxie. Et c\'est dans sa capitale, Trantor, que Hari Seldon invente la psychohistoire, une science nouvelle permettant de prédire l\'avenir.', '7.99', 1, '../../Views/assets/img/produits/fondation.webp', 4),
(5, 'Extraction et Gestion de la Connaissance', 'La sélection d\'articles publiés dans le présent recueil constitue les actes des 23e Journées Internationales Francophones Extraction et Gestion des Connaissances (EGC 2023) qui se sont déroulées à l\'Université Lumière Lyon 2 du 16 janvier au 20 janvier 2023. ', '80.00', 3, '../../Views/assets/img/produits/extractionetgestiondesconnaissances.webp', 2),
(6, 'Analytics', 'By leveraging big data & analytics, businesses create the potential to better understand, manage, and strategically exploiting the complex dynamics of customer behavior', '32.99', 5, '../../Views/assets/img/produits/analytics.jpg', 2);

-- --------------------------------------------------------

--
-- Structure de la table `roles`
--

CREATE TABLE `roles` (
  `id` int(11) NOT NULL,
  `name` varchar(50) CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `roles`
--

INSERT INTO `roles` (`id`, `name`) VALUES
(1, 'Admin'),
(2, 'Client');

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `name` varchar(50) CHARACTER SET utf8 NOT NULL,
  `email` varchar(100) CHARACTER SET utf8 NOT NULL,
  `password` varchar(100) CHARACTER SET utf8 NOT NULL,
  `roleid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `password`, `roleid`) VALUES
(1, 'mehdi mansour', 'mehdi.mansour@univ-lyon2.fr', 'password', 1),
(2, 'pierre dupont', 'pierredupont@gmail.com', 'password', 2),
(3, 'admin', 'admin@gmail.com', 'password', 1),
(4, 'client1', 'client1@gmail.com', 'password', 2),
(5, 'julio', 'julio@gmail.com', 'password', 2),
(6, 'elon', 'elon@gmail.com', 'password', 2),
(7, 'titi', 'titi@gmail.com', 'password', 2),
(8, 'Rasmus Lerdorf', 'super_admin@gmail.com', 'password', 1),
(9, 'Pierre Dupont', 'client_lambda@gmail.com', 'password', 2),
(10, 'jd', 'jd@jd.fr', 'jd', 2);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id`),
  ADD KEY `categoryid` (`categoryid`);

--
-- Index pour la table `roles`
--
ALTER TABLE `roles`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fk_users_roleid` (`roleid`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `categories`
--
ALTER TABLE `categories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT pour la table `products`
--
ALTER TABLE `products`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT pour la table `roles`
--
ALTER TABLE `roles`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT pour la table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `products`
--
ALTER TABLE `products`
  ADD CONSTRAINT `products_ibfk_1` FOREIGN KEY (`categoryid`) REFERENCES `categories` (`id`);

--
-- Contraintes pour la table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `fk_users_roleid` FOREIGN KEY (`roleid`) REFERENCES `roles` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
