/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Eyjafjörður.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaqqad <mnaqqad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:54:59 by mnaqqad           #+#    #+#             */
/*   Updated: 2023/03/23 17:24:32 by mnaqqad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <deque>
#include "header.hpp"
#include "ConfigFile.hpp"

class Server_Eyjafjörður{
    public:
        struct addrinfo hints , *servinfo;
        Server_Eyjafjörður();
        Server_Eyjafjörður(int sk,const char *port);
        int Set_up_Server(const char *port);
    private:
        static int reuse;
        int Server_Socket;
        const char *PORT;
        // std::deuque<>
        // int Status_Code;
        
};