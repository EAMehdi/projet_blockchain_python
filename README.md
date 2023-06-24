# Spécification du Composant HMACSHA512 en C++ et Python

## Auteurs
Mehdi EL AYADI, Romain DIOP, Qilian GU

## Historique des versions
| Version | Date       | Description                 |
|---------|------------|-----------------------------|
| 1.0     | 26/05/2023 | Première version du document|
| 1.5     | 04/06/2023 | Changement de binome & Update de la fonction|
| 2.0     | 23/05/2023 | Update Test & Ajout Installation et Exemples|

## Description

### Contexte
Le composant HMACSHA512 est un module de cryptographie qui fournit une fonction de hachage cryptographique pour la sécurité des données. Il est basé sur l'algorithme HMAC (Hash-based Message Authentication Code) et utilise SHA512 comme fonction de hachage sous-jacente.

### En détails : 

HMACSHA512 est un algorithme de hachage utilisé pour l'authentification de messages. Il est basé sur l'algorithme cryptographique SHA-512. HMAC signifie "Hash-based Message Authentication Code". C'est une construction spécifique utilisée pour créer une fonction de hachage de message, qui peut être utilisée pour vérifier à la fois l'intégrité des données et l'authenticité.

L'algorithme HMACSHA512 combine une **clé secrète** avec le message à hacher pour produire un code d'authentification de message (*MAC - Message authentication code*). Ce MAC peut ensuite être utilisé pour vérifier que le message n'a pas été altéré pendant le transport et que le message provient bien de l'expéditeur prévu.

Les cas d'utilisation typiques de HMACSHA512 comprennent :

- **Authentification de messages** : HMACSHA512 peut être utilisé pour garantir que les messages envoyés sur un réseau n'ont pas été falsifiés. Le destinataire du message peut utiliser le MAC pour vérifier l'intégrité du message.

- **Signature de tokens** : Dans les systèmes d'authentification basés sur des tokens, comme JWT (JSON Web Tokens), HMACSHA512 peut être utilisé pour signer le token. Cela garantit que le token n'a pas été modifié après sa création.

- **Protection des données sensibles** : HMACSHA512 peut être utilisé pour vérifier l'intégrité des données sensibles, comme les mots de passe. En stockant le MAC d'un mot de passe plutôt que le mot de passe lui-même, vous pouvez vérifier un mot de passe sans risquer de le divulguer.

Ce document décrit la spécification d'un composant basé sur l'algorithme HMACSHA512. Ce composant est destiné à être utilisé dans des applications nécessitant une authentification de messages codés en C++ et Python.

### Schéma bloc incluant les composants connexes
```
[Application] --> [HMACSHA512 Composant] --> [SHA512]
```
L'application interagit avec le composant HMACSHA512, qui à son tour utilise le composant SHA512.

### Interface et interaction avec chaque autre composant
L'interface du composant HMACSHA512 est conçue pour être simple et directe. Elle fournit une fonction `hmac_sha512(key, message)` qui prend une clé et un message en entrée, et renvoie le hachage HMACSHA512 du message.

### Résumé: déclarations de fonctions python d’interface et leurs arguments
def hmac_sha512(key: str, message: str) -> str:
    """
    Calcule le HMACSHA512 du message avec la clé donnée.

    Args:
        key (str): La clé utilisée pour le hachage.
        message (str): Le message à hacher.

    Returns:
        str: Le hachage HMACSHA512 du message, représenté comme une chaîne de caractères hexadécimales.
    """

### Cas d’erreurs
Si la clé ou le message ne sont pas de type `str`, une `TypeError` sera levée. Si la clé est vide, une `ValueError` sera levée.

## Test

### Plan de test
Nous testerons la fonction `hmac_sha512` avec différentes clés et messages, y compris des cas limites comme une clé vide ou un message vide. Nous vérifierons que la fonction renvoie le bon hachage et qu'elle lève les exceptions appropriées en cas d'erreur.

### Programme de test
```
import pytest
import crypt_message as crypt

def test_hmac_sha512():
    # Test with valid values
    key = "secret"
    message = "Hello, World!"
    assert crypt.hmac_sha512(key, message) == '9b61...'  # you need to replace '9b61...' with the correct expected hash

    # Test with an empty key
    with pytest.raises(ValueError):
        crypt.hmac_sha512('', message)

    # Test with a key of the wrong type
    with pytest.raises(TypeError):
        crypt.hmac_sha512(123, message)

    # Test with a message of the wrong type
    with pytest.raises(TypeError):
        crypt.hmac_sha512(key, 123)
```
Pour exécuter les tests, utilisez simplement la commande `python -m pytest test_hmac_sha512`.


## Execution du test 

Pour cela il faut suivre les instructions suivantes : 
1. Installation de OpenSSL et Pytest
```bash
sudo apt-get install libssl-dev
pip install pytest
```

2. Cloner le projet et accéder au dossier 
```
git clone https://github.com/EAMehdi/projet_blockchain_python
cd projet_blockchain_python
cd crypt_component
```


3. 

## Exemple d'éxecution pour un test primitif : 
Comparaison en ligne : https://www.devglan.com/online-tools/hmac-sha256-online

![image](https://github.com/EAMehdi/projet_blockchain_python/assets/45198822/8ffb0777-21d1-4b87-8a74-1d5a66731346)

```bash
idhem_aya@instance-1:~/projet_blockchain_python/crypt_component$ make
g++ -fPIC `python3-config --includes` -I ../pybind11/include -I ../json/include -I ../pybind11_json/include -c crypt_message.cpp -o crypt_message.o
g++ -o crypt_message.so -shared  crypt_message.o `python3-config --ldflags` -lssl -lcrypto
echo "execution du test"
execution du test
python3 test.py
Le message original est : Hello, World!
La clé est : secret
Message chiffré : 851caed63934ad1c9a03aef23ba2b84f224bdff4f5148efc57d95f9ae80ca9db2e98bc4c709a529eb1b7234a1ac2e381d28e0eb1efa090bb19613f5c124b6d5b
```
