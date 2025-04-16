# 🌱 Modular Non-Blocking Firmware for Arduino-Based Automation

Un firmware léger, modulaire et non-bloquant conçu pour l'automatisation embarquée sur microcontrôleurs Arduino.  
Initialement développé pour piloter un système hydroponique complet, il peut facilement être adapté à d'autres projets de contrôle environnemental.

---

## 🚀 Présentation

Ce firmware a été pensé pour être **entièrement configurable, modulaire et non bloquant**, s’inspirant de l’architecture du firmware **Marlin (imprimantes 3D)**. Il permet de gérer dynamiquement des capteurs et actionneurs multiples via un système orienté objet, sans bloquer la boucle principale (`loop()`), grâce à l’utilisation de **timers logiciels et d’une liste chaînée de modules actifs**.

Il fonctionne sur **Arduino Nano**, mais peut être porté sur d'autres cartes AVR (Uno, Mega, etc.) et à terme sur des microcontrôleurs plus puissants (ESP32...).

---

## 🧠 Fonctionnalités clés

- ✅ **Système modulaire** : chaque capteur ou actionneur est encapsulé dans une classe indépendante.
- ✅ **Ajout/retrait facile de modules** sans modifier le cœur du firmware.
- ✅ **Architecture non bloquante** : aucun `delay()`, tout est basé sur des timers logiciels.
- ✅ **Configuration via headers (`#define`)** pour activer/désactiver les modules.
- ✅ **Support des capteurs environnementaux** : température, humidité, pH, TDS, sol, etc.
- ✅ **Gestion d'actionneurs variés** : chauffage, ventilation, éclairage, pompes, modules Peltier, ultrasons...
- ✅ **Écran OLED avec animations** : affichage dynamique des données en temps réel.
- ✅ **Contrôle distant** : communication série via un Raspberry Pi / Banana Pi pour pilotage en réseau.
- ✅ **Menu en cours de développement** pour configuration directe via encodeur rotatif.

---

## 🧰 Matériel testé

| Composant               | Rôle                                               |
|------------------------|----------------------------------------------------|
| Arduino Nano           | Microcontrôleur principal                          |
| Raspberry Pi Zero      | Interface réseau / terminal distant                |
| Écran OLED I2C         | Affichage en temps réel avec animations            |
| Capteur DHT / AM2301   | Température & humidité de l'air                    |
| Capteur TDS / pH       | Analyse qualité de l’eau                           |
| Capteurs de sol        | Suivi de l’humidité des pots                       |
| Chauffage / Peltier    | Contrôle thermique de l’eau                        |
| Modules à ultrasons    | Humidification active                              |
| Éclairage LED "esclave"| Gestion automatique de la lumière                 |
| Rotary encoder         | Navigation dans un menu (en dev)                  |

---

## 🖥️ Affichage OLED

L’écran affiche :

- 🌡️ Température et humidité ambiantes
- 🔥 Chauffage actif
- ❄️ Refroidissement actif
- 💦 Ultrason en cours
- 💡 Lumière activée
- 🔧 Paramètres système (bientôt configurables via menu)

---

## 🔧 Installation

1. Clonage

2. Configuration
Activez ou désactivez les modules dans les fichiers config.h, pinout.h, etc.

Définissez vos pins et vos seuils de déclenchement selon votre montage.

3. Téléversement
Ouvrez le projet dans l’IDE Arduino

Sélectionnez Arduino Nano (ATmega328P) ou la carte que vous utilisez

Téléversez le firmware

4. Supervision série (optionnel)
Branchez un Raspberry Pi sur le port série de l’Arduino

Utilisez un outil comme minicom, screen ou un script Python pour envoyer des commandes ou lire les logs

🧭 Exemple de commandes série
Des commandes simples peuvent être envoyées via le port série pour :

Forcer un arrosage

Activer ou désactiver un module

Rebooter un sous-système

(💡 Voir le fichier SerialManager.cpp pour l’implémentation complète)

🚧 Roadmap
 * Menu OLED finalisé avec navigation par encodeur
 * Support ESP32 avec WiFi intégré
 * Système de sauvegarde des paramètres en EEPROM
 * Interface web côté Raspberry Pi (via Flask ou Node)
 * Support I2C/SPI pour extension multi-Arduino

🤝 Contribution
Les contributions sont les bienvenues !
Le projet est principalement destiné à ceux ayant de l’expérience avec les systèmes embarqués, la gestion d’objets et les architectures non bloquantes.

🛑 Disclaimer
Ce projet a été développé dans un but éducatif et personnel, pour apprendre la gestion de systèmes embarqués complexes.
Il n’est associé à aucun usage illégal. Toute ressemblance avec des systèmes de culture illicite est purement fortuite et non encouragée.

📜 Licence
Ce projet est sous **Licence GPLv3**. Vous êtes libre de modifier et redistribuer ce code, à condition que les modifications soient partagées sous la même licence et qu'il ne soit pas utilisé à des fins commerciales.  
Le logiciel est fourni "tel quel", sans garantie d'aucune sorte.

🙌 Auteur
NeoLTK
🔗 github.com/NeoLTK
🛠️ Firmware embarqué & projets DIY d'automatisation
