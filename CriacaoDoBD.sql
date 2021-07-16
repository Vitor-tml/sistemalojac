CREATE DATABASE sistema_de_estoque CHARACTER SET utf8 COLLATE utf8_general_ci;

USE sistema_de_estoque;

CREATE TABLE produtos(
	id int NOT NULL AUTO_INCREMENT,
    nome varchar(30) NOT NULL,
    preco float(7,2) NOT NULL,
    quantidade int DEFAULT '1',
    PRIMARY KEY(id)
)DEFAULT CHARSET = utf8;

DESCRIBE produtos;
