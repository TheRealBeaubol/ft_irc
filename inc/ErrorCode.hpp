/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorCode.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:25:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:13:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME            "001"  // <nick> :Bienvenue sur le serveur
#define RPL_UMODEIS            "221"  // <modes utilisateurs>
#define RPL_CHANNELMODEIS      "324"  // <modes chan>
#define RPL_CREATIONTIME       "329"  // <chan> <timestamp>
#define RPL_NOTOPIC            "331"  // <chan>
#define RPL_TOPIC              "332"  // <chan> <topic>
#define RPL_TOPICWHOTIME       "333"  // <chan> <nick> <timestamp>
#define RPL_INVITING           "341"  // <chan> <nick>
#define RPL_NAMREPLY           "353"  // <chan> <liste des utilisateurs avec status>
#define RPL_ENDOFNAMES         "366"  // <chan>

#define ERR_NOSUCHNICK         "401"  // <nick>
#define ERR_NOSUCHCHANNEL      "403"  // <chan>
#define ERR_NORECIPIENT        "411"  // <>
#define ERR_NOTEXTTOSEND       "412"  // <>
#define ERR_UNKNOWNCOMMAND     "421"  // <commande>
#define ERR_NONICKNAMEGIVEN    "431"  // <nick>
#define ERR_ERRONEUSNICKNAME   "432"  // <nick>
#define ERR_NICKNAMEINUSE      "433"  // <nick>
#define ERR_USERNOTINCHANNEL   "441"
#define ERR_NOTONCHANNEL       "442"  // <chan>
#define ERR_USERONCHANNEL      "443"  // <nick>
#define ERR_NEEDMOREPARAMS     "461"  // <commande>
#define ERR_ALREADYREGISTRED   "462"  // <>
#define ERR_PASSWDMISMATCH     "464"  // <>
#define ERR_KEYSET             "467"  // <chan>
#define ERR_CHANNELISFULL      "471"  // <chan>
#define ERR_UNKNOWNMODE        "472"  // <caractère>
#define ERR_INVITEONLYCHAN     "473"  // <chan>
#define ERR_BADCHANNELKEY      "475"  // <chan>
#define ERR_CHANOPRIVSNEEDED   "482"  // <chan>
#define ERR_USERSDONTMATCH     "502"  // <>