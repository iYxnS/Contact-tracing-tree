# 🦠 Arbre de Traçage des Contacts — Projet Final Structures de Données

Une simulation en C++ d'un **système de traçage des contacts infectieux**, construite à l'aide d'un arbre personnalisé, d'une file d'attente et d'une deque.


## 📌 Description

Ce projet modélise la propagation d'une maladie à partir d'un premier patient infecté (**Patient Zéro**) vers d'autres personnes via une **chaîne de contacts**. Chaque personne infectée est identifiée par un **numéro d'assurance maladie** unique et stockée comme nœud dans un arbre. La structure permet de savoir qui a infecté qui, combien de cas proviennent d'une personne donnée, et de retracer le chemin d'infection jusqu'à sa source.

---

## 🧠 Structures de Données Utilisées

| Structure | Utilisation |
|---|---|
| **Arbre N-aire** | Stocker la chaîne de contacts/infections |
| **Liste chaînée** (`std::list`) | Stocker les enfants directs d'un nœud |
| **File d'attente** (`std::queue`) | Parcours BFS pour rechercher dans l'arbre |
| **Deque** (`std::deque`) | Liste de contacts à double entrée |
| **Templates** | Version générique de ContactList |

---

## ⚙️ Fonctionnalités

- **Ajouter le Patient Zéro** — définit la racine de l'arbre d'infection
- **Ajouter un contact** — enregistre qu'un patient en a infecté un autre
- **Supprimer un contact** — retire un patient et tous ses descendants
- **Afficher un contact** — montre l'ID, les contacts directs, le total de cas et le parent
- **Tracer la source** — remonte d'un nœud jusqu'au Patient Zéro
- **Afficher les cas directs** — liste tous les contacts directs d'un patient
- **Afficher l'arbre complet** — parcours BFS niveau par niveau
- **ContactList (Deque)** — file à double entrée pour gérer les IDs de contacts

---


## 👤 Auteur

**Yasin Sari**
