var Spotify = require("spotify-finder")
const Discord = require('discord.js');
const client = new Discord.Client({
  intents: 3276799
});
const fs = require('fs');
const fsp = require('fs').promises;
const token = "MzYzNjI1OTUzNzgxNjEyNTQ1.GAietZ._McS0q_vOvJsZPRv1Nm6Cf8lt5s2UGEVCxLESI"

const spotifyClient = new Spotify({
  consumer: {
    key: '1cfdfd756a144ecf8f938351d2ed576d',
    secret: '6239416d18294a00a1ccfa40b0025167'
  }
});

function sleep(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

client.on('ready', () => {
  console.log("Pornire cu succes")
});

async function GetUserPresence() {
  const guild = client.guilds.cache.get("595634507600756794");

  var result = [];

  const presencePromise = new Promise((resolve) => {
    guild.members.fetch().then(members => {
      members.forEach(member => {
        if (member.id == "323177297421139968" && member.presence.activities.length != 0) {
          result = member.presence.activities[0];
          resolve(result);
        }
      });
    });
  })

  return presencePromise;
}

async function UpdateMusicDB() {
  try {
    // Get the user presence activity
    var currentPresence = await GetUserPresence();
    if (currentPresence == null) return;

    let data = JSON.parse(fs.readFileSync('melodii.json'));
    var artistAlreadyExist = 0, songAlreadyExists = 0, artistPos, songPos;

    artistName = currentPresence.state;
    songName = currentPresence.details;

    // Logger
    var logContent;
    var d = new Date();
    var ora = d.getHours();
    var minut = d.getMinutes();
    if (minut > 9) logContent = `${ora}:${minut} ${currentPresence.state} - ${currentPresence.details}`;
    else logContent = `${ora}:0${minut} ${currentPresence.state} - ${currentPresence.details}`;
    logContent = logContent + '\n';

    // Check if the previous song is current song. If it is, exit function
    if (!((artistName != data.artist_anterior && songName != data.melodie_anterioara) ||
        (artistName != data.artist_anterior && songName == data.melodie_anterioara) ||
        (artistName == data.artist_anterior && songName != data.melodie_anterioara))) {
      return;
    }

    fs.appendFile('logs.txt', logContent, err => {
      if (err) return
    });

    for (artistIndex = 0; artistIndex < data.artisti.length; artistIndex++) {
      if (data.artisti[artistIndex].formatie == currentPresence.state) {
        artistAlreadyExist = 1;
        artistPos = artistIndex;
      }
      for (songIndex = 0; songIndex < data.artisti[artistIndex].piese.length; songIndex++)
        if (data.artisti[artistIndex].piese[songIndex] == currentPresence.details) {
          songAlreadyExists = 1;
          songPos = songIndex;
        }
    }

    if (artistAlreadyExist == 0) {
      var genreExists, genrePos;
      data['artisti'].push({
        "formatie": currentPresence.state,
        "piese": [currentPresence.details],
        "ascultari": [1]
      });
      let genres = JSON.parse(fs.readFileSync('genres.json'))
      let nume = currentPresence.state.split(";")[0];
      const params = {
        q: nume,
        type: 'artist',
        limit: 5
      }
      spotifyClient.search(params).then(d => {
          if (d.artists.items[0].genres.length > 0) {
            for (externGenresIndex = 0; externGenresIndex < d.artists.items[0].genres.length; externGenresIndex++) {
              genreExists = 0;
              for (jsonGenresIndex = 0; jsonGenresIndex < genres.genuri.length; jsonGenresIndex++) {
                if (genres.genuri[jsonGenresIndex].nume == d.artists.items[0].genres[externGenresIndex]) {
                  genreExists = 1;
                  genrePos = jsonGenresIndex
                }
              }
              if (genreExists == 0) {
                genres["genuri"].push({
                  "nume": d.artists.items[0].genres[externGenresIndex],
                  "ascultari": 1,
                  "artist": [nume]
                });
                fsp.writeFile("genres.json", JSON.stringify(genres));
              } else {
                genres.genuri[genrePos].artist.push(nume);
                genres.genuri[genrePos].ascultari++;
                fsp.writeFile("genres.json", JSON.stringify(genres));
              }
            }
          }
        });
    } else if (songAlreadyExists == 0 && artistAlreadyExist == 1) {
      data.artisti[artistPos].piese.push(currentPresence.details);
      data.artisti[artistPos].ascultari.push(1);
    } else if (songAlreadyExists == 1 && artistAlreadyExist == 1) {
      data.artisti[artistPos].ascultari[songPos]++;
    }
    data.melodie_anterioara = songName;
    data.artist_anterior = artistName;
    data.id_melodie_anterioara = currentPresence.createdTimestamp;
    fsp.writeFile("melodii.json", JSON.stringify(data));
  } catch (er) {
    fs.appendFile('logs.txt', '\n' + er, exception => {
      if (exception) return
    })
  }
}


setInterval(async function () {
  await UpdateMusicDB();
}, 1000);

client.on('messageCreate', async message => {
  try {
    if ((message.author.id == "238718268049719296" || message.author.id == "844090524066512897" || message.author.id == "323177297421139968") && message.content == "!stats") {
      let data = JSON.parse(fs.readFileSync('melodii.json'))
      var i, j, x1 = 0, x2 = 0, x3 = 0, s1, s2, s3, a1, a2, a3, suma, A1, A2, A3, X1 = 0, X2 = 0, X3 = 0, AT = 0, ST = 0, SDT = 0; AT = data.artisti.length;
      for (i = 0; i < data.artisti.length; i++) {
        suma = 0;
        SDT += data.artisti[i].piese.length;
        for (j = 0; j < data.artisti[i].piese.length; j++) {
          ST += data.artisti[i].ascultari[j];
          suma += data.artisti[i].ascultari[j];
          if (data.artisti[i].ascultari[j] > x3) {
            x1 = x2;
            a1 = a2;
            s1 = s2;
            x2 = x3;
            a2 = a3;
            s2 = s3;
            x3 = data.artisti[i].ascultari[j];
            s3 = data.artisti[i].piese[j];
            a3 = data.artisti[i].formatie;
          } else if (data.artisti[i].ascultari[j] > x2) {
            x1 = x2;
            a1 = a2;
            s1 = s2;
            x2 = data.artisti[i].ascultari[j];
            s2 = data.artisti[i].piese[j];
            a2 = data.artisti[i].formatie;
          } else if (data.artisti[i].ascultari[j] > x1) {
            x1 = data.artisti[i].ascultari[j];
            s1 = data.artisti[i].piese[j];
            a1 = data.artisti[i].formatie;
          }
        }
        if (suma > X3) {
          X1 = X2;
          X2 = X3;
          X3 = suma;
          A1 = A2;
          A2 = A3;
          A3 = data.artisti[i].formatie;
        } else if (suma > X2) {
          X1 = X2;
          X2 = suma;
          A1 = A2;
          A2 = data.artisti[i].formatie;
        } else if (suma > X1) {
          X1 = suma;
          A1 = data.artisti[i].formatie;
        }
      }

      const {
        MessageEmbed
      } = require('discord.js');
      const link_spotify = `https://upload.wikimedia.org/wikipedia/commons/thumb/7/74/Spotify_App_Logo.svg/2048px-Spotify_App_Logo.svg.png`;

      const embed = new MessageEmbed()
        .setColor('#7d43d9')
        .setTitle("Mihai's Spotify Wrap")
        .setFooter({
          text: 'Since 16th June 2022',
          iconURL: link_spotify
        })
        .setThumbnail(link_spotify)
        .addFields({
            name: `**Aristi ascultati**`,
            value: `${AT}`,
            inline: true
          }, {
            name: `**Piese diferite**`,
            value: `${SDT}`,
            inline: true
          }, {
            name: `**Total piese ascultate**`,
            value: `${ST}`,
            inline: true
          }, {
            name: '\u200B',
            value: '\u200B'
          }, {
            name: '__**Top 3 Artists**__',
            value: '\u200B'
          }, {
            name: `${A3}`,
            value: `(${X3} ascultari)`,
            inline: true
          }, {
            name: `${A2}`,
            value: `(${X2} ascultari)`,
            inline: true
          }, {
            name: `${A1}`,
            value: `(${X1} ascultari)`,
            inline: true
          }, {
            name: '\u200B',
            value: '\u200B'
          }, {
            name: '__**Top 3 Songs**__',
            value: '\u200B'
          }, {
            name: `${s3}`,
            value: `de ${a3} (${x3} ascultari)`,
            inline: true
          }, {
            name: `${s2}`,
            value: `de ${a2} (${x2} ascultari)`,
            inline: true
          }, {
            name: `${s1}`,
            value: `de ${a1} (${x1} ascultari)`,
            inline: true
          }, {
            name: '\u200B',
            value: '\u200B'
          },

        )
      message.channel.send({
        embeds: [embed]
      });

    } else if ((message.author.id == "238718268049719296" || message.author.id == "844090524066512897" || message.author.id == "323177297421139968") && message.content.startsWith("!genres")) {
      var i, j, nr;
      let genres = JSON.parse(fs.readFileSync('genres.json'))
      const link_spotify = `https://upload.wikimedia.org/wikipedia/commons/thumb/7/74/Spotify_App_Logo.svg/2048px-Spotify_App_Logo.svg.png`;
      let msg = message.content.split(" ")
      if (msg[1] != undefined && msg[1] <= 25) nr = msg[1];
      else nr = 10;
      const {
        MessageEmbed
      } = require('discord.js');
      const embed = new MessageEmbed()
        .setColor('#7d43d9')
        .setTitle(`Mihai's Spotify Wrap`)
        .setDescription(`***Au fost ascultate ${genres.genuri.length} de genuri muzicale diferite***`)
        .setThumbnail(link_spotify)
        .setFooter({
          text: 'Since 16th June 2022',
          iconURL: link_spotify
        })

      const listsorted = genres.genuri.sort((a, b) => b.ascultari - a.ascultari)
      for (i = 1; i <= nr; i++) {
        embed.addField(`${listsorted[i-1].nume} (${listsorted[i-1].ascultari} ascultari)`, `${listsorted[i-1].artist[0]}, ${listsorted[i-1].artist[1]}, ${listsorted[i-1].artist[2]}`, true)
      }
      message.channel.send({
        embeds: [embed]
      });
    } else if ((message.author.id == "238718268049719296" || message.author.id == "844090524066512897" || message.author.id == "323177297421139968") && message.content == "!random") {
      let genres = JSON.parse(fs.readFileSync('genres.json'))
      let gen_curent = genres.genuri[Math.floor(Math.random() * genres.genuri.length)]
      lista_artisti = gen_curent.artist.toString().split(',').join(', ')
      const link_spotify = `https://upload.wikimedia.org/wikipedia/commons/thumb/7/74/Spotify_App_Logo.svg/2048px-Spotify_App_Logo.svg.png`;
      const {
        MessageEmbed
      } = require('discord.js');
      const embed = new MessageEmbed()
        .setColor('#7d43d9')
        .setTitle(`Mihai's Spotify Wrap`)
        .setThumbnail(link_spotify)
        .setFooter({
          text: 'Since 16th June 2022',
          iconURL: link_spotify
        })

      embed.addField(`${gen_curent.nume} (${gen_curent.ascultari} ascultari)`, lista_artisti)
      message.channel.send({
        embeds: [embed]
      });

    } else if ((message.author.id == "238718268049719296" || message.author.id == "844090524066512897" || message.author.id == "323177297421139968") && message.content == "!help") {
      const {
        MessageEmbed
      } = require('discord.js');
      const embed = new MessageEmbed()
        .setColor('#7d43d9')
        .setTitle(`Comenzile mele`)
        .addField('!stats', 'Informatii generale despre activitatea ta pe spotify')
        .addField('!genres <0-25>', 'Top-ul celor mai ascultate genuri muzicale. Daca nu este precizat un argument, se afiseaza top-ul primelor 10 genuri muzicale')
        .addField('!random', 'Se afiseaza un gen muzical la intamplare si se afiseaza toti artistii respectivului gen muzical')

      message.channel.send({
        embeds: [embed]
      });
    }

  } catch (er) {
    console.log(er);
    fs.appendFile('logs.txt', er + '\n', error => {
      if (error) return
    })
  }
});



client.login(token);