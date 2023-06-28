# Spécification du Composant HMACSHA512 en C++ et Python

## Auteurs
Mehdi EL AYADI, Romain DIOP, Qilian GU

## Historique des versions
| Version | Date       | Description                 |
|---------|------------|-----------------------------|
| 1.0     | 26/05/2023 | Première version du document|
| 1.5     | 04/06/2023 | Changement de binome & Update de la fonction|
| 2.0     | 23/05/2023 | Update Test & Ajout Installation et Exemples|
| 2.5     | 28/05/2023 | Update (key hexadecimal de taille fixe) |

## Description

### Contexte
Le composant HMACSHA512 est un module de cryptographie spécialisé dans l'authentification des messages. Il garantit non seulement l'intégrité des données, mais assure aussi leur authenticité grâce à l'utilisation d'une fonction de hachage cryptographique. Fondé sur l'algorithme HMAC (Hash-based Message Authentication Code), HMACSHA512 utilise le SHA512 comme fonction de hachage sous-jacente

### En détails : 

HMACSHA512 est un algorithme de hachage utilisé pour l'authentification de messages. Il est basé sur l'algorithme cryptographique SHA-512. HMAC signifie "Hash-based Message Authentication Code". C'est une construction spécifique utilisée pour créer une fonction de hachage de message, qui peut être utilisée pour vérifier à la fois l'intégrité des données et l'authenticité.

L'algorithme HMACSHA512 combine une **clé secrète** avec le message à hacher pour produire un code d'authentification de message (*MAC - Message authentication code*). Ce MAC peut ensuite être utilisé pour vérifier que le message n'a pas été altéré pendant le transport et que le message provient bien de l'expéditeur prévu.

Une spécificité de cet algorithme réside dans son caractère secret, s'opposant ainsi aux méthodes d'authentification qui reposent sur le système de clés publique et privée. Dans ce cas, la clé HMACSHA512 doit être partagée de manière sécurisée entre l'expéditeur et le destinataire pour garantir un processus d'authentification efficace.

Une modification majeure a été effectuée pour vérifier que la clé fournie est une chaîne hexadécimale de taille fixe 256 bits. De plus, elle doit commencer par "0x" pour indiquer que c'est une chaîne hexadécimale.

Les cas d'utilisation typiques de HMACSHA512 comprennent :

- **Authentification de messages** : HMACSHA512 peut être utilisé pour garantir que les messages envoyés sur un réseau n'ont pas été falsifiés. Le destinataire du message peut utiliser le MAC pour vérifier l'intégrité du message.

- **Signature de tokens** : Dans les systèmes d'authentification basés sur des tokens, comme JWT (JSON Web Tokens), HMACSHA512 peut être utilisé pour signer le token. Cela garantit que le token n'a pas été modifié après sa création.

- **Protection des données sensibles** : HMACSHA512 peut être utilisé pour vérifier l'intégrité des données sensibles, comme les mots de passe. En stockant le MAC d'un mot de passe plutôt que le mot de passe lui-même, vous pouvez vérifier un mot de passe sans risquer de le divulguer.

Ce document décrit la spécification d'un composant basé sur l'algorithme HMACSHA512. Ce composant est destiné à être utilisé dans des applications nécessitant une authentification de messages codés en C++ et Python.

### Interface et interaction avec d'autre composant
L'interface du composant HMACSHA512 est conçue pour être simple et directe. Elle fournit une fonction `hmac_sha512(key, message)` qui prend une clé et un message en entrée, et renvoie le hachage HMACSHA512 du message.

### Résumé: déclarations de fonctions python d’interface et leurs arguments
```python
def hmac_sha512(key: str, message: str) -> str:
    """
    Calcule le HMACSHA512 du message avec la clé donnée.

    Args:
        key (str): La clé utilisée pour le hachage. Doit être une chaîne hexadécimale de taille fixe 256 bits commençant par '0x'.
        message (str): Le message à hacher.

    Returns:
        str: Le hachage HMACSHA512 du message, représenté comme une chaîne de caractères hexadécimales.
    """
```
### Cas d’erreurs
Si la clé ou le message ne sont pas de type str, une TypeError sera levée. Si la clé est vide ou ne respecte pas le format hexadécimal requis (256 bits et commençant par '0x'), une ValueError sera levée.

## Test

### Plan de test
Nous testerons la fonction `hmac_sha512` avec différentes clés et messages, y compris des cas limites comme une clé vide ou un message vide. Nous vérifierons que la fonction renvoie le bon hachage et qu'elle lève les exceptions appropriées en cas d'erreur.

### Programme de test
```python
import pytest
import crypt_message as crypt

def test_hmac_sha512_valid():
    key = "secret"
    message = "Hello, World!"
    assert crypt.hmac_sha512(key, message) == '851caed63934ad1c9a03aef23ba2b84f224bdff4f5148efc57d95f9ae80ca9db2e98bc4c709a529eb1b7234a1ac2e381d28e0eb1efa090bb19613f5c124b6d5b'

def test_hmac_sha512_empty_key():
    message = "Hello, World!"
    with pytest.raises(ValueError):
        crypt.hmac_sha512('', message)

def test_hmac_sha512_wrong_key_type():
    message = "Hello, World!"
    with pytest.raises(TypeError):
        crypt.hmac_sha512(123, message)

def test_hmac_sha512_wrong_message_type():
    key = "secret"
    with pytest.raises(TypeError):
        crypt.hmac_sha512(key, 123)
```
Pour exécuter les tests, utilisez simplement la commande `python -m pytest test_hmac_sha512`.


## Execution du test 

Pour cela il faut suivre les instructions suivantes : 
1. Installation de OpenSSL et Pytest
```console
sudo apt-get install libssl-dev
pip install pytest
```

2. Cloner le projet et accéder au dossier 
```console
git clone https://github.com/EAMehdi/projet_blockchain_python
cd projet_blockchain_python/
cd crypt_component/
```


3. Executer le test :
```console
make
```

Voici le résultat :
```console
idhem_aya@instance-1:~/projet_blockchain_python/crypt_component$ make
echo "execution du test"
execution du test
pytest test.py
================================================== test session starts ==================================================
platform linux -- Python 3.9.2, pytest-7.4.0, pluggy-1.2.0
rootdir: /home/idhem_aya/projet_blockchain_python/crypt_component
collected 4 items                                                                                                       

test.py ....                                                                                                      [100%]

=================================================== 4 passed in 0.02s ===================================================
```

## Exemple d'éxecution pour un test primitif : 
Comparaison en ligne : https://www.liavaag.org/English/SHA-Generator/HMAC/

![image](https://github.com/EAMehdi/projet_blockchain_python/assets/45198822/3199cd31-cc42-4c81-8936-3e5a7fa79635)

```console
idhem_aya@instance-1:~/projet_blockchain_python/crypt_component$ make
g++ -fPIC `python3-config --includes` -I ../pybind11/include -I ../json/include -I ../pybind11_json/include -c crypt_message.cpp -o crypt_message.o
g++ -o crypt_message.so -shared  crypt_message.o `python3-config --ldflags` -lssl -lcrypto
echo "execution du test"
execution du test
python3 test.py
Le message original est  Hello, World!
La clé est :  0x7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d
Le message chiffré est :
 51d746531a26bd58baf64c02e73df5bb4586aca6d61a73f26008319ee33c42b9e7c8b000494fc2c33b101a60623710db11f11ef35976b064f3b00ce39ff0c1fc
```
