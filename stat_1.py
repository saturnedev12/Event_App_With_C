import matplotlib.pyplot as plt
import datetime

# Lire les dates et les valeurs à partir du fichier texte
dates = []
values = []
with open('data.txt') as f:
    for line in f:
        date_str, value_str = line.strip().split(',')
        date = datetime.datetime.strptime(date_str, '%Y-%m-%d').date()
        value = int(value_str)
        dates.append(date)
        values.append(value)

# Créer la figure et les axes
fig, ax = plt.subplots()

# Ajouter les données à la courbe
ax.plot(dates, values)

# Formater les dates sur l'axe des x
date_ticks = [date for date in dates if date.day == 1]  # afficher une date par mois
ax.set_xticks(date_ticks)
ax.set_xticklabels([date.strftime('%Y-%m-%d') for date in date_ticks], rotation=45)

# Ajouter une légende
ax.set_title('Statistique de evenement')
ax.set_xlabel('Date')
ax.set_ylabel('Valeur')
ax.legend(['Valeurs'])

# Afficher la courbe
plt.show()
