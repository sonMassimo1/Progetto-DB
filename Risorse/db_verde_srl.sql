-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Specie_di_Piante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Specie_di_Piante` (
  `COD_Pianta` VARCHAR(6) NOT NULL,
  `Nom_latino` VARCHAR(45) NOT NULL,
  `Nom_comune` VARCHAR(45) NOT NULL,
  `Tipo` ENUM("interno", "esterno") NOT NULL,
  `esotica` TINYINT NOT NULL,
  PRIMARY KEY (`COD_Pianta`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`LISTINO`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`LISTINO` (
  `Prezzo` DOUBLE UNSIGNED NOT NULL,
  `Data_inizio` DATETIME NOT NULL,
  `Data_fine` DATETIME NULL,
  `Pianta_listino` VARCHAR(6) NOT NULL,
  INDEX `fk_LISTINO_Specie_di_Piante_idx` (`Pianta_listino` ASC) VISIBLE,
  PRIMARY KEY (`Pianta_listino`, `Data_inizio`),
  CONSTRAINT `fk_LISTINO_Specie_di_Piante`
    FOREIGN KEY (`Pianta_listino`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Colore`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Colore` (
  `Colore` VARCHAR(20) NOT NULL,
  `ID_colore` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`ID_colore`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Colore_has_Specie_di_Piante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Colore_has_Specie_di_Piante` (
  `Colore_ID_colore` INT NOT NULL,
  `ID_Fiorita` VARCHAR(6) NOT NULL,
  PRIMARY KEY (`Colore_ID_colore`, `ID_Fiorita`),
  INDEX `fk_Colore_has_Specie_di_Piante_Specie_di_Piante1_idx` (`ID_Fiorita` ASC) VISIBLE,
  INDEX `fk_Colore_has_Specie_di_Piante_Colore1_idx` (`Colore_ID_colore` ASC) VISIBLE,
  CONSTRAINT `fk_Colore_has_Specie_di_Piante_Colore1`
    FOREIGN KEY (`Colore_ID_colore`)
    REFERENCES `mydb`.`Colore` (`ID_colore`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Colore_has_Specie_di_Piante_Specie_di_Piante1`
    FOREIGN KEY (`ID_Fiorita`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Fornitori`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Fornitori` (
  `idFornitori` INT NOT NULL AUTO_INCREMENT,
  `cod_fis` VARCHAR(16) NOT NULL,
  `Nome_fornitore` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idFornitori`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Specie_di_Piante_has_Fornitori`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Specie_di_Piante_has_Fornitori` (
  `Pianta_Fornita` VARCHAR(6) NOT NULL,
  `Fornitore` INT NOT NULL,
  PRIMARY KEY (`Pianta_Fornita`, `Fornitore`),
  INDEX `fk_Specie_di_Piante_has_Fornitori_Fornitori1_idx` (`Fornitore` ASC) VISIBLE,
  INDEX `fk_Specie_di_Piante_has_Fornitori_Specie_di_Piante1_idx` (`Pianta_Fornita` ASC) VISIBLE,
  CONSTRAINT `fk_Specie_di_Piante_has_Fornitori_Specie_di_Piante1`
    FOREIGN KEY (`Pianta_Fornita`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Specie_di_Piante_has_Fornitori_Fornitori1`
    FOREIGN KEY (`Fornitore`)
    REFERENCES `mydb`.`Fornitori` (`idFornitori`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`INDIRIZZI`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`INDIRIZZI` (
  `indirizzo` VARCHAR(64) NOT NULL,
  `Fornitori_idFornitori` INT NOT NULL,
  INDEX `fk_INDIRIZZI_Fornitori1_idx` (`Fornitori_idFornitori` ASC) VISIBLE,
  PRIMARY KEY (`indirizzo`, `Fornitori_idFornitori`),
  CONSTRAINT `fk_INDIRIZZI_Fornitori1`
    FOREIGN KEY (`Fornitori_idFornitori`)
    REFERENCES `mydb`.`Fornitori` (`idFornitori`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`MAGAZZINO`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`MAGAZZINO` (
  `Giacenza` INT UNSIGNED NOT NULL,
  `Pianta` VARCHAR(6) NOT NULL,
  PRIMARY KEY (`Pianta`),
  CONSTRAINT `fk_MAGAZZINO_Specie_di_Piante1`
    FOREIGN KEY (`Pianta`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Cliente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Cliente` (
  `COD_C` VARCHAR(16) NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `ind_fatt` VARCHAR(45) NOT NULL,
  `ind_sped` VARCHAR(45) NOT NULL,
  `ind_resid` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`COD_C`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`ORDINI`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`ORDINI` (
  `idORDINI` INT NOT NULL,
  `dataAcq` DATETIME NOT NULL,
  `Cliente` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`idORDINI`),
  INDEX `fk_ORDINI_Cliente1_idx` (`Cliente` ASC) VISIBLE,
  CONSTRAINT `fk_ORDINI_Cliente1`
    FOREIGN KEY (`Cliente`)
    REFERENCES `mydb`.`Cliente` (`COD_C`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`ORDINI_has_Specie_di_Piante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`ORDINI_has_Specie_di_Piante` (
  `ORDINI_idORDINI` INT NOT NULL,
  `Specie` VARCHAR(6) NOT NULL,
  `Quantita` INT NOT NULL,
  PRIMARY KEY (`ORDINI_idORDINI`, `Specie`),
  INDEX `fk_ORDINI_has_Specie_di_Piante_Specie_di_Piante1_idx` (`Specie` ASC) VISIBLE,
  INDEX `fk_ORDINI_has_Specie_di_Piante_ORDINI1_idx` (`ORDINI_idORDINI` ASC) VISIBLE,
  CONSTRAINT `fk_ORDINI_has_Specie_di_Piante_ORDINI1`
    FOREIGN KEY (`ORDINI_idORDINI`)
    REFERENCES `mydb`.`ORDINI` (`idORDINI`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_ORDINI_has_Specie_di_Piante_Specie_di_Piante1`
    FOREIGN KEY (`Specie`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PACCHI`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PACCHI` (
  `idPACCHI` INT NOT NULL,
  `Ordine` INT NOT NULL,
  PRIMARY KEY (`idPACCHI`),
  INDEX `fk_PACCHI_ORDINI1_idx` (`Ordine` ASC) VISIBLE,
  CONSTRAINT `fk_PACCHI_ORDINI1`
    FOREIGN KEY (`Ordine`)
    REFERENCES `mydb`.`ORDINI` (`idORDINI`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PACCHI_has_Specie_di_Piante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PACCHI_has_Specie_di_Piante` (
  `PACCHI_idPACCHI` INT NOT NULL,
  `Pianta_Pacco` VARCHAR(6) NOT NULL,
  PRIMARY KEY (`PACCHI_idPACCHI`, `Pianta_Pacco`),
  INDEX `fk_PACCHI_has_Specie_di_Piante_Specie_di_Piante1_idx` (`Pianta_Pacco` ASC) VISIBLE,
  INDEX `fk_PACCHI_has_Specie_di_Piante_PACCHI1_idx` (`PACCHI_idPACCHI` ASC) VISIBLE,
  CONSTRAINT `fk_PACCHI_has_Specie_di_Piante_PACCHI1`
    FOREIGN KEY (`PACCHI_idPACCHI`)
    REFERENCES `mydb`.`PACCHI` (`idPACCHI`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_PACCHI_has_Specie_di_Piante_Specie_di_Piante1`
    FOREIGN KEY (`Pianta_Pacco`)
    REFERENCES `mydb`.`Specie_di_Piante` (`COD_Pianta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Referente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Referente` (
  `Nome_referente` VARCHAR(45) NOT NULL,
  `Cognome_referente` VARCHAR(45) NOT NULL,
  `Rivendita` VARCHAR(11) NOT NULL,
  INDEX `fk_Referente_Cliente1_idx` (`Rivendita` ASC) VISIBLE,
  PRIMARY KEY (`Rivendita`, `Cognome_referente`),
  CONSTRAINT `fk_Referente_Cliente1`
    FOREIGN KEY (`Rivendita`)
    REFERENCES `mydb`.`Cliente` (`COD_C`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Contatti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Contatti` (
  `tipo` ENUM("email", "cel", "tel") NOT NULL,
  `Valore` VARCHAR(45) NOT NULL,
  `preferito` TINYINT NOT NULL,
  `Cliente_COD_C` VARCHAR(16) NOT NULL,
  INDEX `fk_Contatti_Cliente1_idx` (`Cliente_COD_C` ASC) VISIBLE,
  PRIMARY KEY (`Cliente_COD_C`, `Valore`),
  CONSTRAINT `fk_Contatti_Cliente1`
    FOREIGN KEY (`Cliente_COD_C`)
    REFERENCES `mydb`.`Cliente` (`COD_C`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`utenti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`utenti` (
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(32) NOT NULL,
  `ruolo` ENUM("operatore", "Manager") NOT NULL,
  PRIMARY KEY (`username`));

USE `mydb` ;

-- -----------------------------------------------------
-- procedure Visualizza_Pianta
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `Visualizza_Pianta`(IN var_Pianta VARCHAR(6))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
if((select count(*)
	from Specie_di_Piante
    where COD_Pianta = var_Pianta)>0)
    then
	select distinct Nom_latino, Nom_comune, Tipo, esotica, Giacenza
    from Specie_di_Piante, MAGAZZINO
    where var_Pianta = COD_Pianta and Pianta=var_Pianta;
else
signal sqlstate '45002' set message_text ="Pianta non trovata";
end if;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Visualizzare_Storico_Prezzo
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Visualizzare_Storico_Prezzo`(IN var_Pianta VARCHAR(6))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if((select count(*)
	from Specie_di_Piante
    where var_Pianta = COD_Pianta)>0)
    then
	select *
    from LISTINO
    where Pianta_listino = var_Pianta;
else signal sqlstate '45002' set message_text="Pianta non trovata";
end if;
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Visualizzare_Colorazioni
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Visualizzare_Colorazioni`(IN var_Pianta VARCHAR(6))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if((select count(*)
	from Specie_di_Piante
    where var_Pianta = COD_Pianta)>0)
    then
	select distinct Nom_latino, Nom_comune, Tipo, esotica, Colore
    from Specie_di_Piante, Colore_has_Specie_di_Piante, Colore
    where var_Pianta = COD_Pianta and var_Pianta = ID_Fiorita and Colore_ID_colore = ID_colore;
else
signal sqlstate '45002' set message_text='Pianta non trovata';
end if;
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Visualizza_ordine
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Visualizza_ordine`(IN ordine int)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if((select count(*)
	from ORDINI
    where idORDINI = ordine)>0)
    then
	if((select  count(*)
		from ORDINI, ORDINI_has_Specie_di_Piante, Cliente, Contatti, Referente
		where ordine = ORDINI.idORDINI and Cliente.COD_C = ORDINI.Cliente and  Cliente.COD_C = Contatti.Cliente_COD_C and ORDINI_has_Specie_di_Piante.ORDINI_idORDINI = ordine  and Cliente.COD_C = Referente.Rivendita) > 0)
		then
		select  dataAcq, ORDINI_has_Specie_di_Piante.Specie, Quantita,Cliente.COD_C, Cliente.Nome, Cliente.ind_sped, Contatti.tipo, Contatti.Valore, Referente.Nome_referente, Referente.Cognome_referente
		from ORDINI, ORDINI_has_Specie_di_Piante, Cliente, Contatti, Referente
		where ordine = ORDINI.idORDINI and Cliente.COD_C = ORDINI.Cliente and  Cliente.COD_C = Contatti.Cliente_COD_C and ORDINI_has_Specie_di_Piante.ORDINI_idORDINI = ordine and Cliente.COD_C = Referente.Rivendita and Contatti.preferito =1;
    else
		select  distinct dataAcq, ORDINI_has_Specie_di_Piante.Specie, Quantita,Cliente.COD_C, Cliente.Nome, Cliente.ind_sped, Contatti.tipo, Contatti.Valore
		from ORDINI, ORDINI_has_Specie_di_Piante, Cliente, Contatti
		where (ordine = ORDINI.idORDINI and Cliente.COD_C = ORDINI.Cliente and  Cliente.COD_C = Contatti.Cliente_COD_C and ORDINI_has_Specie_di_Piante.ORDINI_idORDINI = ordine and Contatti.preferito=1);
    end if;
else
signal sqlstate '45003' set message_text='Ordine non trovato';
end if;
commit;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Visualizza_ordini_cliente
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Visualizza_ordini_cliente`(IN COD_CLI VARCHAR(16))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if((select count(*)
	from Cliente
    where COD_CLI = COD_C)>0)
    then
	select distinct idORDINI, dataAcq, ORDINI_has_Specie_di_Piante.Specie, Quantita 
    from ORDINI, ORDINI_has_Specie_di_Piante
    where COD_CLI = Cliente and idORDINI = ORDINI_idORDINI;
else 
signal sqlstate '45005' set message_text="Cliente non trovato";
end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Visualizzare_piante_Pacco
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Visualizzare_piante_Pacco`(in id_pacco int)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if((select count(*)
	from PACCHI
    where id_pacco= idPACCHI)>0)
    then
	select Pianta_Pacco, Nom_comune, Nom_latino, Ordine, Quantita
    from PACCHI_has_Specie_di_Piante, Specie_di_Piante, PACCHI, ORDINI, ORDINI_has_Specie_di_Piante
    where PACCHI_idPACCHI = id_pacco and Pianta_Pacco = COD_Pianta and id_pacco=idPACCHI and Ordine = idORDINI and idORDINI=ORDINI_idORDINI;
    else 
    signal sqlstate '45006' set message_text="Pacco non trovato";
    end if;
    commit;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizzare_piante_inserire_pacco
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `visualizzare_piante_inserire_pacco`(in ordine int)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
	if((select count(*)
		from ORDINI
        where ordine = idORDINI)>0)
        then
		select Specie
		from ORDINI_has_Specie_di_Piante
		where ORDINI_idORDINI = ordine and Specie NOT IN (select Pianta_Pacco as Specie
														from PACCHI_has_Specie_di_Piante, PACCHI
														where PACCHI.ordine = ordine and idPACCHI = PACCHI_idPACCHI);
	else
		signal sqlstate '45003' set message_text='Ordine non trovato';
end if;
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiornare_Giacenze
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiornare_Giacenze`(in Specie_pianta varchar(6),in giac int)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
	set transaction isolation level repeatable read ;
    start transaction;
    if(Specie_pianta in (select COD_Pianta
						from Specie_di_Piante))
                        then
		update MAGAZZINO
		SET Giacenza = Giacenza + giac
		where Pianta = Specie_pianta ;
	else
    signal sqlstate '45002' set message_text=' Pianta non trovata';
    end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Modificare_prezzo_pianta
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Modificare_prezzo_pianta`(in Specie_pianta varchar(6), in Nuovo_prezzo double)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level serializable;
start transaction;
if((select count(*)
	from Specie_di_Piante
	where Specie_pianta = COD_Pianta)>0)
    then
    update LISTINO
    set Data_fine = NOW()
    where Pianta_listino = Specie_pianta and Data_fine is null;
   insert into LISTINO(Prezzo, Data_inizio, Pianta_listino) values (Nuovo_prezzo,NOW() ,Specie_pianta);
else
signal sqlstate '45002'set message_text="Pianta non trovata";
end if;
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungere_specie_pianta
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE  PROCEDURE `aggiungere_specie_pianta`(in codice varchar(6), in n_com varchar(45), in n_lat varchar(45), in posizione enum('interno', 'esterno'), in eso TINYINT, in quantita int, in Costo double, in cod_for int)
BEGIN
set transaction isolation level repeatable read;
start transaction;
	insert into Specie_di_Piante(COD_Pianta, Nom_latino, Nom_comune, Tipo, esotica) values (codice, n_lat, n_com, posizione, eso) ;
	insert into LISTINO(Prezzo, Data_inizio, Pianta_listino) values (Costo, NOW() ,codice);
	insert into MAGAZZINO(Giacenza, Pianta) values (quantita, codice);
    insert into Specie_di_Piante_has_Fornitori(Pianta_Fornita, Fornitore) values (codice, cod_for);
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_cliente_privato
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_cliente_privato`(in cod varchar(16), in nom varchar(45), in fat varchar(45),in sped varchar(45), in res varchar(45),in tipo_contatto ENUM('email', 'cel', 'tel'), in valore_contatto varchar(45))
BEGIN
	insert into Cliente(COD_C, Nome, ind_fatt, ind_sped, ind_resid) values(cod, nom, fat, sped, res);
    insert into Contatti(tipo, Valore, preferito, Cliente_COD_C) values(tipo_contatto, valore_contatto, 1, cod);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_cliente_rivendita
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_cliente_rivendita`(in cod varchar(11), in nom varchar(45), in fat varchar(45),in sped varchar(45), in res varchar(45),in tipo_contatto ENUM('email', 'cel', 'tel'), in valore_contatto varchar(45), in n_ref varchar(45), in c_ref varchar(45))
BEGIN
	insert into Cliente(COD_C, Nome, ind_fatt, ind_sped, ind_resid) values(cod, nom, fat, sped, res);
    insert into Contatti(tipo, Valore, preferito, Cliente_COD_C) values(tipo_contatto, valore_contatto,1, cod);
    insert into Referente(Nome_referente, Cognome_referente, Rivendita) values (n_ref, c_ref, cod);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_ordine
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_ordine`(in id int, in cod_cliente varchar(16))
BEGIN
	insert into ORDINI(idORDINI, dataAcq, Cliente) values (id, NOW(), cod_cliente);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure agg_piante_ordine
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `agg_piante_ordine`(in ordine int, in pianta VARCHAR(6), in quant int)
BEGIN
	insert into ORDINI_has_Specie_di_Piante(ORDINI_idORDINI, Specie, Quantita) values (ordine, pianta, quant);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_contatto
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `aggiungi_contatto`(in cod_Cliente varchar(16), in tipo_contatto ENUM('email', 'cel', 'tel'), in valore_contatto varchar(45))
BEGIN
	 insert into Contatti(tipo, Valore, preferito, Cliente_COD_C) values(tipo_contatto, valore_contatto, 0, cod_Cliente);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure scegli_contatto_preferito
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `scegli_contatto_preferito`(in cliente varchar(16), in valore_contatto varchar(45))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
if(valore_contatto in (select Valore from Contatti where Cliente_COD_C = cliente))
then
	if ((select count(*)
		from Contatti
        where cliente = Cliente_COD_C and preferito = 1)>0)
        then update Contatti set preferito = 0 where cliente = Cliente_COD_C;
	end if;
	update Contatti set preferito = 1 where valore_contatto = Valore and cliente = Cliente_COD_C;
else
signal sqlstate '45004' set message_text='Contatto non trovato';

end if;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_piante_a_pacco
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_piante_a_pacco`(in idpacco int,in pianta varchar(6))
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
set transaction isolation level repeatable read;
start transaction;
if (pianta in (select Specie
					from ORDINI_has_Specie_di_Piante, ORDINI, PACCHI
					where ORDINI_has_Specie_di_Piante.ORDINI_idORDINI = ORDINI.idORDINI and ORDINI.idORDINI = PACCHI.ordine and PACCHI.idPACCHI = idpacco
                    and ORDINI_has_Specie_di_Piante.Specie NOT IN (select Pianta_Pacco as Specie
													from PACCHI_has_Specie_di_Piante
													where idpacco = PACCHI_idPACCHI)))
                                                    THEN
	insert into PACCHI_has_Specie_di_Piante(PACCHI_idPACCHI, Pianta_Pacco) values (idpacco, pianta);
    else
   signal sqlstate '45001' set message_text=' Pianta non valida';
    END IF;
commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_colore_pianta
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_colore_pianta`(in colorazione varchar(20), in pianta varchar(6) )
BEGIN

	if((select count(*)
		from Colore
        where Colore =colorazione) = 0)
		then insert into Colore (Colore) values (colorazione) ; 
	end if;
    insert into Colore_has_Specie_di_Piante(id_Fiorita, Colore_ID_colore) values (pianta, (select ID_colore
																								from Colore
                                                                                                where Colore =colorazione));
																						
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_fornitori_pianta
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `visualizza_fornitori_pianta`(in pianta varchar(6) )
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
if((select count(*)
	from Specie_di_Piante
    where pianta = COD_Pianta)>0)
    then
	select idFornitori, cod_fis as 'codice fiscale', Nome_fornitore as 'Nome', Pianta_Fornita as 'Pianta', indirizzo
    from Fornitori, Specie_di_Piante_has_Fornitori, INDIRIZZI
    where pianta = Specie_di_Piante_has_Fornitori.Pianta_Fornita and Specie_di_Piante_has_Fornitori.Fornitore = Fornitori.idFornitori and Fornitori.idFornitori = INDIRIZZI.Fornitori_idFornitori;
else 
 signal sqlstate '45002'set message_text="Pianta non trovata";
 end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `login`(in var_username varchar(45), in var_pass varchar(45), out var_role INT)
BEGIN
	declare var_user_role ENUM('operatore', 'Manager');
    
	select `ruolo` from `utenti`
		where `username` = var_username
        and `password` = md5(var_pass)
        into var_user_role;
        
        -- See the corresponding enum in the client
		if var_user_role = 'operatore' then
			set var_role = 1;
		elseif var_user_role = 'Manager' then
			set var_role = 2;
		else
			set var_role = 3;
		end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure Aggiungi_pacco
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `Aggiungi_pacco`(in ordine int, in pacco int)
BEGIN
	insert into PACCHI(idPACCHI, Ordine) values (pacco, ordine);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_totale_ordine
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `visualizza_totale_ordine`(in ordine int)
BEGIN
declare exit handler for sqlexception
begin 
	rollback;
    resignal;
end;
    set transaction isolation level read committed;
    start transaction;
    if((select count(*)
		from ORDINI
        where idORDINI = ordine)>0)
        then
		select sum(Prezzo * quantita) as 'Totale'
		from LISTINO, Specie_di_Piante, ORDINI_has_Specie_di_Piante, ORDINI
		where ordine = ORDINI_idORDINI and ordine=idORDINI and dataAcq>=Data_inizio  and (dataAcq<=Data_fine or Data_fine is null) and Pianta_listino = COD_Pianta and COD_Pianta = Specie;
	else
		signal sqlstate '45003' set message_text= 'Ordine non trovato';
    end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure crea_utente
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `crea_utente`(IN username VARCHAR(45), IN pass VARCHAR(32), IN ruolo enum('Manager','operatore'))
BEGIN
	insert into utenti(username,password, ruolo) VALUES(username, MD5(pass), ruolo);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_fornitore_specie
-- -----------------------------------------------------

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `aggiungi_fornitore_specie`(in cod int, in pianta varchar(6))
BEGIN

insert into Specie_di_Piante_has_Fornitori(Pianta_Fornita, Fornitore) values(pianta, cod);
END$$

DELIMITER ;
CREATE USER 'operatore' IDENTIFIED BY 'operatore';

GRANT EXECUTE ON procedure `mydb`.`agg_piante_ordine` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_cliente_privato` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_cliente_rivendita` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`aggiungi_contatto` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_ordine` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_piante_a_pacco` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`scegli_contatto_preferito` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizza_ordine` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizza_ordini_cliente` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`visualizzare_piante_inserire_pacco` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizzare_piante_Pacco` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizzare_Storico_Prezzo` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_pacco` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizza_Pianta` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`visualizza_totale_ordine` TO 'operatore';
GRANT EXECUTE ON procedure `mydb`.`Visualizzare_Colorazioni` TO 'operatore';
CREATE USER 'Manager' IDENTIFIED BY 'Manager';

GRANT EXECUTE ON procedure `mydb`.`aggiungere_specie_pianta` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Aggiungi_colore_pianta` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Modificare_prezzo_pianta` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Visualizzare_Storico_Prezzo` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`visualizza_fornitori_pianta` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`crea_utente` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Visualizza_Pianta` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Visualizzare_Colorazioni` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`Aggiornare_Giacenze` TO 'Manager';
GRANT EXECUTE ON procedure `mydb`.`visualizza_totale_ordine` TO 'Manager';
CREATE USER 'login' IDENTIFIED BY 'login';

GRANT EXECUTE ON procedure `mydb`.`login` TO 'login';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
USE `mydb`;

DELIMITER $$
USE `mydb`$$
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`ORDINI_has_Specie_di_Piante_BEFORE_INSERT` BEFORE INSERT ON `ORDINI_has_Specie_di_Piante` FOR EACH ROW
BEGIN
	
	if((NEW.Quantita)>(select Giacenza
						from mydb.MAGAZZINO, Specie_di_Piante
						where mydb.MAGAZZINO.Pianta = Specie_di_Piante.COD_Pianta and NEW.Specie = Specie_di_Piante.COD_Pianta))
                        then
						signal sqlstate '45000' set message_text=' Non ci sono abbastanza Piante in magazzino';
	else update MAGAZZINO
		set Giacenza = Giacenza - NEW.Quantita
        where MAGAZZINO.Pianta = NEW.Specie;
	end if;																					
END$$


DELIMITER ;


call mydb.crea_utente('admin', 'admin', 'Manager');
INSERT INTO `mydb`.`Fornitori` (`idFornitori`, `cod_fis`, `Nome_fornitore`) VALUES ('1', 'aaabbb12c34d567e', 'Mario Rossi');
INSERT INTO `mydb`.`Fornitori` (`idFornitori`, `cod_fis`, `Nome_fornitore`) VALUES ('2', 'xxxyyy12z34t567e', 'Carlo Flora');
INSERT INTO `mydb`.`Fornitori` (`idFornitori`, `cod_fis`, `Nome_fornitore`) VALUES ('3', '01786610894', 'Piante co.');
INSERT INTO `mydb`.`Fornitori` (`idFornitori`, `cod_fis`, `Nome_fornitore`) VALUES ('4', '12345678910', 'EXPOLANT');
INSERT INTO `mydb`.`Fornitori` (`idFornitori`, `cod_fis`, `Nome_fornitore`) VALUES ('5', '10987654321', 'naturarbor');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via del corso, 1', '1');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Brombeis, 8', '2');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via dei Tribunali, 5', '2');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Po, 101', '3');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Viale Crispi, 74', '3');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Tuscolana, 404', '4');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Casilina, 102', '4');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Cassia, 104', '4');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Prenestina, 500', '4');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Viale Bovio, 15', '5');
INSERT INTO `mydb`.`INDIRIZZI` (`indirizzo`, `Fornitori_idFornitori`) VALUES ('Via Cona, 19', '5');

